mm_do_pam_account(void)
{
	Buffer m;
	u_int ret;
	char *msg;

	debug3("%s entering", __func__);
	if (!options.use_pam)
		fatal("UsePAM=no, but ended up in %s anyway", __func__);

	buffer_init(&m);
	mm_request_send(pmonitor->m_recvfd, MONITOR_REQ_PAM_ACCOUNT, &m);

	mm_request_receive_expect(pmonitor->m_recvfd,
	    MONITOR_ANS_PAM_ACCOUNT, &m);
	ret = buffer_get_int(&m);
	msg = buffer_get_string(&m, NULL);
	buffer_append(&loginmsg, msg, strlen(msg));
	free(msg);

	buffer_free(&m);

	debug3("%s returning %d", __func__, ret);

	return (ret);
}
