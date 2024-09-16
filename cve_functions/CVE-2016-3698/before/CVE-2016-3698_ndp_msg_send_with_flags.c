int ndp_msg_send_with_flags(struct ndp *ndp, struct ndp_msg *msg, uint8_t flags)
{
	enum ndp_msg_type msg_type = ndp_msg_type(msg);

	if (ndp_msg_type_info(msg_type)->addrto_adjust)
		ndp_msg_type_info(msg_type)->addrto_adjust(&msg->addrto);

	switch (msg_type) {
		case NDP_MSG_NA:
			if (flags & ND_OPT_NA_UNSOL) {
				ndp_msgna_flag_override_set((struct ndp_msgna*)&msg->nd_msg, true);
				ndp_msgna_flag_solicited_set((struct ndp_msgna*)&msg->nd_msg, false);
				ndp_msg_addrto_adjust_all_nodes(&msg->addrto);
			} else {
				ndp_msgna_flag_solicited_set((struct ndp_msgna*)&msg->nd_msg, true);
			}
			break;
		default:
			break;
	}

	return mysendto6(ndp->sock, msg->buf, msg->len, 0,
			 &msg->addrto, msg->ifindex);
}
