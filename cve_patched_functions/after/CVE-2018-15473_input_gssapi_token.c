input_gssapi_token(int type, u_int32_t plen, struct ssh *ssh)
{
	Authctxt *authctxt = ssh->authctxt;
	Gssctxt *gssctxt;
	gss_buffer_desc send_tok = GSS_C_EMPTY_BUFFER;
	gss_buffer_desc recv_tok;
	OM_uint32 maj_status, min_status, flags;
	u_char *p;
	size_t len;
	int r;

	if (authctxt == NULL || (authctxt->methoddata == NULL && !use_privsep))
		fatal("No authentication or GSSAPI context");

	gssctxt = authctxt->methoddata;
	if ((r = sshpkt_get_string(ssh, &p, &len)) != 0 ||
	    (r = sshpkt_get_end(ssh)) != 0)
		fatal("%s: %s", __func__, ssh_err(r));

	recv_tok.value = p;
	recv_tok.length = len;
	maj_status = PRIVSEP(ssh_gssapi_accept_ctx(gssctxt, &recv_tok,
	    &send_tok, &flags));

	free(p);

	if (GSS_ERROR(maj_status)) {
		if (send_tok.length != 0) {
			if ((r = sshpkt_start(ssh,
			    SSH2_MSG_USERAUTH_GSSAPI_ERRTOK)) != 0 ||
			    (r = sshpkt_put_string(ssh, send_tok.value,
			    send_tok.length)) != 0 ||
			    (r = sshpkt_send(ssh)) != 0)
				fatal("%s: %s", __func__, ssh_err(r));
		}
		authctxt->postponed = 0;
		ssh_dispatch_set(ssh, SSH2_MSG_USERAUTH_GSSAPI_TOKEN, NULL);
		userauth_finish(ssh, 0, "gssapi-with-mic", NULL);
	} else {
		if (send_tok.length != 0) {
			if ((r = sshpkt_start(ssh,
			    SSH2_MSG_USERAUTH_GSSAPI_TOKEN)) != 0 ||
			    (r = sshpkt_put_string(ssh, send_tok.value,
			    send_tok.length)) != 0 ||
			    (r = sshpkt_send(ssh)) != 0)
				fatal("%s: %s", __func__, ssh_err(r));
		}
		if (maj_status == GSS_S_COMPLETE) {
			ssh_dispatch_set(ssh, SSH2_MSG_USERAUTH_GSSAPI_TOKEN, NULL);
			if (flags & GSS_C_INTEG_FLAG)
				ssh_dispatch_set(ssh, SSH2_MSG_USERAUTH_GSSAPI_MIC,
				    &input_gssapi_mic);
			else
				ssh_dispatch_set(ssh,
				    SSH2_MSG_USERAUTH_GSSAPI_EXCHANGE_COMPLETE,
				    &input_gssapi_exchange_complete);
		}
	}

	gss_release_buffer(&min_status, &send_tok);
	return 0;
}
