static void *ndp_msg_payload_opts_offset(struct ndp_msg *msg, int offset)
{
	unsigned char *ptr = ndp_msg_payload_opts(msg);

	return ptr + offset;
}
