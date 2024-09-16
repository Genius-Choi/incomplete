size_t ndp_msg_payload_maxlen(struct ndp_msg *msg)
{
	return sizeof(msg->buf);
}
