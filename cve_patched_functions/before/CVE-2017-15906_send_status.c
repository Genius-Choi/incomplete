send_status(u_int32_t id, u_int32_t status)
{
	struct sshbuf *msg;
	int r;

	debug3("request %u: sent status %u", id, status);
	if (log_level > SYSLOG_LEVEL_VERBOSE ||
	    (status != SSH2_FX_OK && status != SSH2_FX_EOF))
		logit("sent status %s", status_to_message(status));
	if ((msg = sshbuf_new()) == NULL)
		fatal("%s: sshbuf_new failed", __func__);
	if ((r = sshbuf_put_u8(msg, SSH2_FXP_STATUS)) != 0 ||
	    (r = sshbuf_put_u32(msg, id)) != 0 ||
	    (r = sshbuf_put_u32(msg, status)) != 0)
		fatal("%s: buffer error: %s", __func__, ssh_err(r));
	if (version >= 3) {
		if ((r = sshbuf_put_cstring(msg,
		    status_to_message(status))) != 0 ||
		    (r = sshbuf_put_cstring(msg, "")) != 0)
			fatal("%s: buffer error: %s", __func__, ssh_err(r));
	}
	send_msg(msg);
	sshbuf_free(msg);
}
