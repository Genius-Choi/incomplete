int ndp_msg_new(struct ndp_msg **p_msg, enum ndp_msg_type msg_type)
{
	struct ndp_msg *msg;

	if (msg_type == NDP_MSG_ALL)
		return -EINVAL;
	msg = ndp_msg_alloc();
	if (!msg)
		return -ENOMEM;
	ndp_msg_init(msg, msg_type);
	*p_msg = msg;
	return 0;
}
