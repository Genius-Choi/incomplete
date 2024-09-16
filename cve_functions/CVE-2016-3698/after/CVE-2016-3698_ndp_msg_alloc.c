static struct ndp_msg *ndp_msg_alloc(void)
{
	struct ndp_msg *msg;

	msg = myzalloc(sizeof(*msg));
	if (!msg)
		return NULL;
	msg->icmp6_hdr = (struct icmp6_hdr *) msg->buf;
	return msg;
}
