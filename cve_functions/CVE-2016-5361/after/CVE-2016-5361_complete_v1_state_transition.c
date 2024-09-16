void complete_v1_state_transition(struct msg_digest **mdp, stf_status result)
{
	struct msg_digest *md = *mdp;
	enum state_kind from_state;
	struct state *st;

	passert(md != NULL);

	/* handle oddball/meta results now */

	switch (result) {
	case STF_SUSPEND:
		cur_state = md->st;	/* might have changed */
		/* FALL THROUGH */
	case STF_INLINE:	/* all done, including release_any_md */
		*mdp = NULL;	/* take md away from parent */
		/* FALL THROUGH */
	case STF_IGNORE:
		DBG(DBG_CONTROL,
		    DBG_log("complete v1 state transition with %s",
			    enum_show(&stfstatus_name, result)));
		return;

	default:
		break;
	}

	DBG(DBG_CONTROL,
	    DBG_log("complete v1 state transition with %s",
		result > STF_FAIL ?
		    enum_name(&ikev1_notify_names, result - STF_FAIL) :
		    enum_name(&stfstatus_name, result)));

	/* safe to refer to *md */

	from_state = md->from_state;

	cur_state = st = md->st; /* might have changed */

	passert(st != NULL);

	passert(!st->st_calculating);

	switch (result) {
	case STF_OK:
	{
		/* advance the state */
		const struct state_microcode *smc = md->smc;

		libreswan_log("transition from state %s to state %s",
			      enum_name(&state_names, from_state),
			      enum_name(&state_names, smc->next_state));

		/* accept info from VID because we accept this message */

		/* If state has FRAGMENTATION support, import it */
		if (md->fragvid) {
			DBG(DBG_CONTROLMORE, DBG_log("peer supports fragmentation"));
			st->st_seen_fragvid = TRUE;
		}

		/* If state has DPD support, import it */
		if (md->dpd &&
		    st->hidden_variables.st_peer_supports_dpd != md->dpd) {
			DBG(DBG_DPD, DBG_log("peer supports dpd"));
			st->hidden_variables.st_peer_supports_dpd = md->dpd;

			if (dpd_active_locally(st)) {
				DBG(DBG_DPD, DBG_log("dpd is active locally"));
			}
		}

		/* If state has VID_NORTEL, import it to activate workaround */
		if (md->nortel) {
			DBG(DBG_CONTROLMORE, DBG_log("peer requires Nortel Contivity workaround"));
			st->st_seen_nortel_vid = TRUE;
		}

		if (!st->st_msgid_reserved &&
		    IS_CHILD_SA(st) &&
		    st->st_msgid != v1_MAINMODE_MSGID) {
			struct state *p1st = state_with_serialno(
				st->st_clonedfrom);

			if (p1st != NULL) {
				/* do message ID reservation */
				reserve_msgid(p1st, st->st_msgid);
			}

			st->st_msgid_reserved = TRUE;
		}

		change_state(st, smc->next_state);

		/* XAUTH negotiation withOUT modecfg ends in STATE_XAUTH_I1
		 * which is wrong and creates issues further in several places
		 * As per libreswan design, it seems every phase 1 negotiation
		 * including xauth/modecfg must end with STATE_MAIN_I4 to mark
		 * actual end of phase 1. With modecfg, negotiation ends with
		 * STATE_MAIN_I4 already.
		 */
#if 0	/* ??? what's this code for? */
		if (st->st_connection->spd.this.xauth_client
		    && st->hidden_variables.st_xauth_client_done
		    && !st->st_connection->spd.this.modecfg_client
		    && st->st_state == STATE_XAUTH_I1) {
			DBG(DBG_CONTROL,
				DBG_log("As XAUTH is done and modecfg is not configured, so Phase 1 neogtiation finishes successfully"));
			change_state(st, STATE_MAIN_I4);
		}
#endif

		/* Schedule for whatever timeout is specified */
		if (!md->event_already_set) {
			/* Delete previous retransmission event.
			 * New event will be scheduled below.
			 */
			delete_event(st);
		}

		/* Delete IKE fragments */
		release_fragments(st);

		/* update the previous packet history */
		remember_received_packet(st, md);

		/* free previous transmit packet */
		freeanychunk(st->st_tpacket);

		/* in aggressive mode, there will be no reply packet in transition
		 * from STATE_AGGR_R1 to STATE_AGGR_R2
		 */
		if (nat_traversal_enabled) {
			/* adjust our destination port if necessary */
			nat_traversal_change_port_lookup(md, st);
		}

		/* if requested, send the new reply packet */
		if (smc->flags & SMF_REPLY) {
			DBG(DBG_CONTROL, {
				ipstr_buf b;
				DBG_log("sending reply packet to %s:%u (from port %u)",
					ipstr(&st->st_remoteaddr, &b),
					st->st_remoteport,
					st->st_interface->port);
			});

			close_output_pbs(&reply_stream); /* good form, but actually a no-op */

			record_and_send_ike_msg(st, &reply_stream,
				enum_name(&state_names, from_state));
		}

		/* Schedule for whatever timeout is specified */
		if (!md->event_already_set) {
			unsigned long delay_ms; /* delay is in milliseconds here */
			enum event_type kind = smc->timeout_event;
			bool agreed_time = FALSE;
			struct connection *c = st->st_connection;

			switch (kind) {
			case EVENT_v1_RETRANSMIT: /* Retransmit packet */
				delay_ms = c->r_interval;
				break;

			case EVENT_SA_REPLACE: /* SA replacement event */
				if (IS_PHASE1(st->st_state) ||
				    IS_PHASE15(st->st_state )) {
					/* Note: we will defer to the "negotiated" (dictated)
					 * lifetime if we are POLICY_DONT_REKEY.
					 * This allows the other side to dictate
					 * a time we would not otherwise accept
					 * but it prevents us from having to initiate
					 * rekeying.  The negative consequences seem
					 * minor.
					 */
					delay_ms = deltamillisecs(c->sa_ike_life_seconds);
					if ((c->policy & POLICY_DONT_REKEY) ||
					    delay_ms >= deltamillisecs(st->st_oakley.life_seconds))
					{
						agreed_time = TRUE;
						delay_ms = deltamillisecs(st->st_oakley.life_seconds);
					}
				} else {
					/* Delay is min of up to four things:
					 * each can limit the lifetime.
					 */
					time_t delay = deltasecs(c->sa_ipsec_life_seconds);

#define clamp_delay(trans) { \
		if (st->trans.present && \
		    delay >= deltasecs(st->trans.attrs.life_seconds)) { \
			agreed_time = TRUE; \
			delay = deltasecs(st->trans.attrs.life_seconds); \
		} \
	}
					clamp_delay(st_ah);
					clamp_delay(st_esp);
					clamp_delay(st_ipcomp);
					delay_ms = delay * 1000;
#undef clamp_delay
				}

				/* By default, we plan to rekey.
				 *
				 * If there isn't enough time to rekey, plan to
				 * expire.
				 *
				 * If we are --dontrekey, a lot more rules apply.
				 * If we are the Initiator, use REPLACE_IF_USED.
				 * If we are the Responder, and the dictated time
				 * was unacceptable (too large), plan to REPLACE
				 * (the only way to ratchet down the time).
				 * If we are the Responder, and the dictated time
				 * is acceptable, plan to EXPIRE.
				 *
				 * Important policy lies buried here.
				 * For example, we favour the initiator over the
				 * responder by making the initiator start rekeying
				 * sooner.  Also, fuzz is only added to the
				 * initiator's margin.
				 *
				 * Note: for ISAKMP SA, we let the negotiated
				 * time stand (implemented by earlier logic).
				 */
				if (agreed_time &&
				    (c->policy & POLICY_DONT_REKEY)) {
					kind = (smc->flags & SMF_INITIATOR) ?
					       EVENT_SA_REPLACE_IF_USED :
					       EVENT_SA_EXPIRE;
				}
				if (kind != EVENT_SA_EXPIRE) {
					time_t marg =
						deltasecs(c->sa_rekey_margin);

					if (smc->flags & SMF_INITIATOR) {
						marg += marg *
							c->sa_rekey_fuzz /
							100.E0 *
							(rand() /
							 (RAND_MAX + 1.E0));
					} else {
						marg /= 2;
					}

					if (delay_ms > (unsigned long)marg * 1000) {
						delay_ms -= (unsigned long)marg * 1000;
						st->st_margin = deltatime(marg);
					} else {
						kind = EVENT_SA_EXPIRE;
					}
				}
				break;

			default:
				bad_case(kind);
			}
			event_schedule_ms(kind, delay_ms, st);
		}

		/* tell whack and log of progress */
		{
			const char *story = enum_name(&state_stories,
						      st->st_state);
			enum rc_type w = RC_NEW_STATE + st->st_state;
			char sadetails[512];

			passert(st->st_state < STATE_IKE_ROOF);

			sadetails[0] = '\0';

			/* document IPsec SA details for admin's pleasure */
			if (IS_IPSEC_SA_ESTABLISHED(st->st_state)) {
				fmt_ipsec_sa_established(st, sadetails,
							 sizeof(sadetails));
			} else if (IS_ISAKMP_SA_ESTABLISHED(st->st_state) &&
				   !st->hidden_variables.st_logged_p1algos) {
				fmt_isakmp_sa_established(st, sadetails,
							  sizeof(sadetails));
			}

			if (IS_ISAKMP_SA_ESTABLISHED(st->st_state) ||
			    IS_IPSEC_SA_ESTABLISHED(st->st_state)) {
				/* log our success */
				w = RC_SUCCESS;
			}

			/* tell whack and logs our progress */
			loglog(w,
			       "%s: %s%s",
			       enum_name(&state_names, st->st_state),
			       story,
			       sadetails);
		}

		/*
		 * make sure that a DPD event gets created for a new phase 1
		 * SA.
		 */
		if (IS_ISAKMP_SA_ESTABLISHED(st->st_state)) {
			if (deltasecs(st->st_connection->dpd_delay) > 0 &&
			    deltasecs(st->st_connection->dpd_timeout) > 0) {
				/* don't ignore failure */
				/* ??? in fact, we do ignore this:
				 * result is NEVER used
				 * (clang 3.4 noticed this)
				 */
				stf_status s = dpd_init(st);

				pexpect(s != STF_FAIL);
				if (s == STF_FAIL)
					result = STF_FAIL; /* ??? fall through !?! */
			}
		}

		/* Special case for XAUTH server */
		if (st->st_connection->spd.this.xauth_server) {
			if (st->st_oakley.doing_xauth &&
			    IS_ISAKMP_SA_ESTABLISHED(st->st_state)) {
				DBG(DBG_CONTROL,
						DBG_log("XAUTH: "
						       "Sending XAUTH Login/Password Request"));
				event_schedule_ms(EVENT_v1_SEND_XAUTH,
						EVENT_v1_SEND_XAUTH_DELAY, st);
						break;
			}
		}

		/*
		 * for XAUTH client, we are also done, because we need to
		 * stay in this state, and let the server query us
		 */
		if (!IS_QUICK(st->st_state) &&
		    st->st_connection->spd.this.xauth_client &&
		    !st->hidden_variables.st_xauth_client_done) {
			DBG(DBG_CONTROL,
			    DBG_log("XAUTH client is not yet authenticated"));
			break;
		}

		/*
		 * when talking to some vendors, we need to initiate a mode
		 * cfg request to get challenged, but there is also an
		 * override in the form of a policy bit.
		 */
		DBG(DBG_CONTROL,
		    DBG_log("modecfg pull: %s policy:%s %s",
			    (st->quirks.modecfg_pull_mode ?
			     "quirk-poll" : "noquirk"),
			    (st->st_connection->policy & POLICY_MODECFG_PULL) ?
			    "pull" : "push",
			    (st->st_connection->spd.this.modecfg_client ?
			     "modecfg-client" : "not-client")));

		if (st->st_connection->spd.this.modecfg_client &&
		    IS_ISAKMP_SA_ESTABLISHED(st->st_state) &&
		    (st->quirks.modecfg_pull_mode ||
		     st->st_connection->policy & POLICY_MODECFG_PULL) &&
		    !st->hidden_variables.st_modecfg_started) {
			DBG(DBG_CONTROL,
			    DBG_log("modecfg client is starting due to %s",
				    st->quirks.modecfg_pull_mode ? "quirk" :
				    "policy"));
			modecfg_send_request(st);
			break;
		}

		/* Should we set the peer's IP address regardless? */
		if (st->st_connection->spd.this.modecfg_server &&
		    IS_ISAKMP_SA_ESTABLISHED(st->st_state) &&
		    !st->hidden_variables.st_modecfg_vars_set &&
		    !(st->st_connection->policy & POLICY_MODECFG_PULL)) {
			change_state(st, STATE_MODE_CFG_R1);
			set_cur_state(st);
			libreswan_log("Sending MODE CONFIG set");
			modecfg_start_set(st);
			break;
		}

		/*
		 * If we are the responder and the client is in "Contivity mode",
		 * we need to initiate Quick mode
		 */
		if (!(smc->flags & SMF_INITIATOR) &&
		    IS_MODE_CFG_ESTABLISHED(st->st_state) &&
		    (st->st_seen_nortel_vid)) {
			libreswan_log("Nortel 'Contivity Mode' detected, starting Quick Mode");
			change_state(st, STATE_MAIN_R3); /* ISAKMP is up... */
			set_cur_state(st);
			quick_outI1(st->st_whack_sock, st, st->st_connection,
				    st->st_connection->policy, 1, SOS_NOBODY
#ifdef HAVE_LABELED_IPSEC
				    , NULL /* Setting NULL as this is responder and will not have sec ctx from a flow*/
#endif
				    );
			break;
		}

		/* wait for modecfg_set */
		if (st->st_connection->spd.this.modecfg_client &&
		    IS_ISAKMP_SA_ESTABLISHED(st->st_state) &&
		    !st->hidden_variables.st_modecfg_vars_set) {
			DBG(DBG_CONTROL,
			    DBG_log("waiting for modecfg set from server"));
			break;
		}

		if (st->st_rekeytov2) {
			DBG(DBG_CONTROL,
			    DBG_log("waiting for IKEv1 -> IKEv2 rekey"));
			break;
		}

		DBG(DBG_CONTROL,
		    DBG_log("phase 1 is done, looking for phase 2 to unpend"));

		if (smc->flags & SMF_RELEASE_PENDING_P2) {
			/* Initiate any Quick Mode negotiations that
			 * were waiting to piggyback on this Keying Channel.
			 *
			 * ??? there is a potential race condition
			 * if we are the responder: the initial Phase 2
			 * message might outrun the final Phase 1 message.
			 *
			 * so, instead of actually sending the traffic now,
			 * we schedule an event to do so.
			 *
			 * but, in fact, quick_mode will enqueue a cryptographic operation
			 * anyway, which will get done "later" anyway, so maybe it is just fine
			 * as it is.
			 *
			 */
			unpend(st);
		}

		if (IS_ISAKMP_SA_ESTABLISHED(st->st_state) ||
		    IS_IPSEC_SA_ESTABLISHED(st->st_state))
			release_whack(st);

		if (IS_QUICK(st->st_state))
			break;

		break;
	}

	case STF_INTERNAL_ERROR:
		/* update the previous packet history */
		remember_received_packet(st, md);

		whack_log(RC_INTERNALERR + md->note,
			  "%s: internal error",
			  enum_name(&state_names, st->st_state));

		DBG(DBG_CONTROL,
		    DBG_log("state transition function for %s had internal error",
			    enum_name(&state_names, from_state)));
		break;

	case STF_TOOMUCHCRYPTO:
		/* ??? Why is this comment useful:
		 * well, this should never happen during a whack, since
		 * a whack will always force crypto.
		 */
		/* ??? why no call of remember_received_packet? */
		unset_suspended(st);
		libreswan_log(
			"message in state %s ignored due to cryptographic overload",
			enum_name(&state_names, from_state));
		log_crypto_workers();
		/* ??? the ikev2.c version used to FALL THROUGH to STF_FATAL */
		break;

	case STF_FATAL:
		/* update the previous packet history */
		remember_received_packet(st, md);

		whack_log(RC_FATAL,
			  "encountered fatal error in state %s",
			  enum_name(&state_names, st->st_state));
#ifdef HAVE_NM
		if (st->st_connection->remotepeertype == CISCO &&
		    st->st_connection->nmconfigured) {
			if (!do_command(st->st_connection,
					&st->st_connection->spd,
					"disconnectNM", st))
				DBG(DBG_CONTROL,
				    DBG_log("sending disconnect to NM failed, you may need to do it manually"));
		}
#endif
		release_pending_whacks(st, "fatal error");
		delete_state(st);
		md->st = st = NULL;
		break;

	default:        /* a shortcut to STF_FAIL, setting md->note */
		passert(result > STF_FAIL);
		md->note = result - STF_FAIL;
		/* FALL THROUGH */
	case STF_FAIL:
		/* As it is, we act as if this message never happened:
		 * whatever retrying was in place, remains in place.
		 */
		/*
		 * ??? why no call of remember_received_packet?
		 * Perhaps because the message hasn't been authenticated?
		 * But then then any duplicate would lose too, I would think.
		 */
		whack_log(RC_NOTIFICATION + md->note,
			  "%s: %s", enum_name(&state_names, st->st_state),
			  enum_name(&ikev1_notify_names, md->note));

		if (md->note != NOTHING_WRONG)
			SEND_NOTIFICATION(md->note);

		DBG(DBG_CONTROL,
		    DBG_log("state transition function for %s failed: %s",
			    enum_name(&state_names, from_state),
			    enum_name(&ikev1_notify_names, md->note)));

#ifdef HAVE_NM
		if (st->st_connection->remotepeertype == CISCO &&
		    st->st_connection->nmconfigured) {
			if (!do_command(st->st_connection,
					&st->st_connection->spd,
					"disconnectNM", st))
				DBG(DBG_CONTROL,
				    DBG_log("sending disconnect to NM failed, you may need to do it manually"));
		}
#endif
		if (IS_PHASE1_INIT(st->st_state)) {
			delete_event(st);
			release_whack(st);
		}
		if (IS_QUICK(st->st_state)) {
			delete_state(st);
			/* wipe out dangling pointer to st */
			md->st = NULL;
		}
		break;
	}
}
