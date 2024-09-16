struct ndp_msgns *ndp_msgns(struct ndp_msg *msg)
{
	if (ndp_msg_type(msg) != NDP_MSG_NS)
		return NULL;
	return &msg->nd_msg.ns;
}
