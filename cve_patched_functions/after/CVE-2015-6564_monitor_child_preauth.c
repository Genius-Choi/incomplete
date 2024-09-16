monitor_child_preauth(Authctxt *_authctxt, struct monitor *pmonitor)
{
	struct mon_table *ent;
	int authenticated = 0, partial = 0;

	debug3("preauth child monitor started");

	close(pmonitor->m_recvfd);
	close(pmonitor->m_log_sendfd);
	pmonitor->m_log_sendfd = pmonitor->m_recvfd = -1;

	authctxt = _authctxt;
	memset(authctxt, 0, sizeof(*authctxt));

	authctxt->loginmsg = &loginmsg;

	if (compat20) {
		mon_dispatch = mon_dispatch_proto20;

		/* Permit requests for moduli and signatures */
		monitor_permit(mon_dispatch, MONITOR_REQ_MODULI, 1);
		monitor_permit(mon_dispatch, MONITOR_REQ_SIGN, 1);
	} else {
		mon_dispatch = mon_dispatch_proto15;

		monitor_permit(mon_dispatch, MONITOR_REQ_SESSKEY, 1);
	}

	/* The first few requests do not require asynchronous access */
	while (!authenticated) {
		partial = 0;
		auth_method = "unknown";
		auth_submethod = NULL;
		authenticated = (monitor_read(pmonitor, mon_dispatch, &ent) == 1);

		/* Special handling for multiple required authentications */
		if (options.num_auth_methods != 0) {
			if (!compat20)
				fatal("AuthenticationMethods is not supported"
				    "with SSH protocol 1");
			if (authenticated &&
			    !auth2_update_methods_lists(authctxt,
			    auth_method, auth_submethod)) {
				debug3("%s: method %s: partial", __func__,
				    auth_method);
				authenticated = 0;
				partial = 1;
			}
		}

		if (authenticated) {
			if (!(ent->flags & MON_AUTHDECIDE))
				fatal("%s: unexpected authentication from %d",
				    __func__, ent->type);
			if (authctxt->pw->pw_uid == 0 &&
			    !auth_root_allowed(auth_method))
				authenticated = 0;
#ifdef USE_PAM
			/* PAM needs to perform account checks after auth */
			if (options.use_pam && authenticated) {
				Buffer m;

				buffer_init(&m);
				mm_request_receive_expect(pmonitor->m_sendfd,
				    MONITOR_REQ_PAM_ACCOUNT, &m);
				authenticated = mm_answer_pam_account(pmonitor->m_sendfd, &m);
				buffer_free(&m);
			}
#endif
		}
		if (ent->flags & (MON_AUTHDECIDE|MON_ALOG)) {
			auth_log(authctxt, authenticated, partial,
			    auth_method, auth_submethod);
			if (!partial && !authenticated)
				authctxt->failures++;
		}
	}

	if (!authctxt->valid)
		fatal("%s: authenticated invalid user", __func__);
	if (strcmp(auth_method, "unknown") == 0)
		fatal("%s: authentication method name unknown", __func__);

	debug("%s: %s has been authenticated by privileged process",
	    __func__, authctxt->user);

	mm_get_keystate(pmonitor);

	/* Drain any buffered messages from the child */
	while (pmonitor->m_log_recvfd != -1 && monitor_read_log(pmonitor) == 0)
		;

	close(pmonitor->m_sendfd);
	close(pmonitor->m_log_recvfd);
	pmonitor->m_sendfd = pmonitor->m_log_recvfd = -1;
}
