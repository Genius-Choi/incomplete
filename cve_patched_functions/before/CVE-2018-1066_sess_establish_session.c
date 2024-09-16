sess_establish_session(struct sess_data *sess_data)
{
	struct cifs_ses *ses = sess_data->ses;

	mutex_lock(&ses->server->srv_mutex);
	if (!ses->server->session_estab) {
		if (ses->server->sign) {
			ses->server->session_key.response =
				kmemdup(ses->auth_key.response,
				ses->auth_key.len, GFP_KERNEL);
			if (!ses->server->session_key.response) {
				mutex_unlock(&ses->server->srv_mutex);
				return -ENOMEM;
			}
			ses->server->session_key.len =
						ses->auth_key.len;
		}
		ses->server->sequence_number = 0x2;
		ses->server->session_estab = true;
	}
	mutex_unlock(&ses->server->srv_mutex);

	cifs_dbg(FYI, "CIFS session established successfully\n");
	spin_lock(&GlobalMid_Lock);
	ses->status = CifsGood;
	ses->need_reconnect = false;
	spin_unlock(&GlobalMid_Lock);

	return 0;
}
