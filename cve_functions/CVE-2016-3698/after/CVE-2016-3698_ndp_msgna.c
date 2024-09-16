struct ndp_msgna *ndp_msgna(struct ndp_msg *msg)
{
	if (ndp_msg_type(msg) != NDP_MSG_NA)
		return NULL;
	return &msg->nd_msg.na;
}
