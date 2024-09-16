struct ndp_msgra *ndp_msgra(struct ndp_msg *msg)
{
	if (ndp_msg_type(msg) != NDP_MSG_RA)
		return NULL;
	return &msg->nd_msg.ra;
}
