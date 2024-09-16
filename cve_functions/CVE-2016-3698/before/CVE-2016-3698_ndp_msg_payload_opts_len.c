size_t ndp_msg_payload_opts_len(struct ndp_msg *msg)
{
	return msg->len - (msg->opts_start - msg->buf);
}
