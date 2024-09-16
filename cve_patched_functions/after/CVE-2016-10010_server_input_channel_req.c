server_input_channel_req(int type, u_int32_t seq, void *ctxt)
{
	Channel *c;
	int id, reply, success = 0;
	char *rtype;

	id = packet_get_int();
	rtype = packet_get_string(NULL);
	reply = packet_get_char();

	debug("server_input_channel_req: channel %d request %s reply %d",
	    id, rtype, reply);

	if ((c = channel_lookup(id)) == NULL)
		packet_disconnect("server_input_channel_req: "
		    "unknown channel %d", id);
	if (!strcmp(rtype, "eow@openssh.com")) {
		packet_check_eom();
		chan_rcvd_eow(c);
	} else if ((c->type == SSH_CHANNEL_LARVAL ||
	    c->type == SSH_CHANNEL_OPEN) && strcmp(c->ctype, "session") == 0)
		success = session_input_channel_req(c, rtype);
	if (reply && !(c->flags & CHAN_CLOSE_SENT)) {
		packet_start(success ?
		    SSH2_MSG_CHANNEL_SUCCESS : SSH2_MSG_CHANNEL_FAILURE);
		packet_put_int(c->remote_id);
		packet_send();
	}
	free(rtype);
	return 0;
}
