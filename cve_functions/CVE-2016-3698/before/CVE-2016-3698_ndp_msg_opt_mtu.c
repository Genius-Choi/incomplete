uint32_t ndp_msg_opt_mtu(struct ndp_msg *msg, int offset)
{
	struct nd_opt_mtu *mtu = ndp_msg_payload_opts_offset(msg, offset);

	return ntohl(mtu->nd_opt_mtu_mtu);
}
