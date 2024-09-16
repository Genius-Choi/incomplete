struct ndp_msgr *ndp_msgr(struct ndp_msg *msg)
{
	if (ndp_msg_type(msg) != NDP_MSG_R)
		return NULL;
	return &msg->nd_msg.r;
}
