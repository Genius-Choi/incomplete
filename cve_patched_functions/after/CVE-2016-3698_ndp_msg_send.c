int ndp_msg_send(struct ndp *ndp, struct ndp_msg *msg)
{
	return ndp_msg_send_with_flags(ndp, msg, ND_OPT_NORMAL);
}
