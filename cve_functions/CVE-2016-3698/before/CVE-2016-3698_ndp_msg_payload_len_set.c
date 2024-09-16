void ndp_msg_payload_len_set(struct ndp_msg *msg, size_t len)
{
	if (len > sizeof(msg->buf))
		len = sizeof(msg->buf);
	msg->len = len;
}
