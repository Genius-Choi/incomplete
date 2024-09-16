enum ndp_msg_type ndp_msg_type(struct ndp_msg *msg)
{
	enum ndp_msg_type msg_type;
	int err;

	err = ndp_msg_type_by_raw_type(&msg_type, msg->icmp6_hdr->icmp6_type);
	/* Type should be always set correctly (ensured by ndp_msg_init) */
	BUG_ON(err);
	return msg_type;
}
