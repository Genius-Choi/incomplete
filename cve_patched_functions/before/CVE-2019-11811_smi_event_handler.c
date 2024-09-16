static enum si_sm_result smi_event_handler(struct smi_info *smi_info,
					   int time)
{
	enum si_sm_result si_sm_result;

restart:
	/*
	 * There used to be a loop here that waited a little while
	 * (around 25us) before giving up.  That turned out to be
	 * pointless, the minimum delays I was seeing were in the 300us
	 * range, which is far too long to wait in an interrupt.  So
	 * we just run until the state machine tells us something
	 * happened or it needs a delay.
	 */
	si_sm_result = smi_info->handlers->event(smi_info->si_sm, time);
	time = 0;
	while (si_sm_result == SI_SM_CALL_WITHOUT_DELAY)
		si_sm_result = smi_info->handlers->event(smi_info->si_sm, 0);

	if (si_sm_result == SI_SM_TRANSACTION_COMPLETE) {
		smi_inc_stat(smi_info, complete_transactions);

		handle_transaction_done(smi_info);
		goto restart;
	} else if (si_sm_result == SI_SM_HOSED) {
		smi_inc_stat(smi_info, hosed_count);

		/*
		 * Do the before return_hosed_msg, because that
		 * releases the lock.
		 */
		smi_info->si_state = SI_NORMAL;
		if (smi_info->curr_msg != NULL) {
			/*
			 * If we were handling a user message, format
			 * a response to send to the upper layer to
			 * tell it about the error.
			 */
			return_hosed_msg(smi_info, IPMI_ERR_UNSPECIFIED);
		}
		goto restart;
	}

	/*
	 * We prefer handling attn over new messages.  But don't do
	 * this if there is not yet an upper layer to handle anything.
	 */
	if (si_sm_result == SI_SM_ATTN || smi_info->got_attn) {
		unsigned char msg[2];

		if (smi_info->si_state != SI_NORMAL) {
			/*
			 * We got an ATTN, but we are doing something else.
			 * Handle the ATTN later.
			 */
			smi_info->got_attn = true;
		} else {
			smi_info->got_attn = false;
			smi_inc_stat(smi_info, attentions);

			/*
			 * Got a attn, send down a get message flags to see
			 * what's causing it.  It would be better to handle
			 * this in the upper layer, but due to the way
			 * interrupts work with the SMI, that's not really
			 * possible.
			 */
			msg[0] = (IPMI_NETFN_APP_REQUEST << 2);
			msg[1] = IPMI_GET_MSG_FLAGS_CMD;

			start_new_msg(smi_info, msg, 2);
			smi_info->si_state = SI_GETTING_FLAGS;
			goto restart;
		}
	}

	/* If we are currently idle, try to start the next message. */
	if (si_sm_result == SI_SM_IDLE) {
		smi_inc_stat(smi_info, idles);

		si_sm_result = start_next_msg(smi_info);
		if (si_sm_result != SI_SM_IDLE)
			goto restart;
	}

	if ((si_sm_result == SI_SM_IDLE)
	    && (atomic_read(&smi_info->req_events))) {
		/*
		 * We are idle and the upper layer requested that I fetch
		 * events, so do so.
		 */
		atomic_set(&smi_info->req_events, 0);

		/*
		 * Take this opportunity to check the interrupt and
		 * message enable state for the BMC.  The BMC can be
		 * asynchronously reset, and may thus get interrupts
		 * disable and messages disabled.
		 */
		if (smi_info->supports_event_msg_buff || smi_info->io.irq) {
			start_check_enables(smi_info);
		} else {
			smi_info->curr_msg = alloc_msg_handle_irq(smi_info);
			if (!smi_info->curr_msg)
				goto out;

			start_getting_events(smi_info);
		}
		goto restart;
	}

	if (si_sm_result == SI_SM_IDLE && smi_info->timer_running) {
		/* Ok it if fails, the timer will just go off. */
		if (del_timer(&smi_info->si_timer))
			smi_info->timer_running = false;
	}

out:
	return si_sm_result;
}
