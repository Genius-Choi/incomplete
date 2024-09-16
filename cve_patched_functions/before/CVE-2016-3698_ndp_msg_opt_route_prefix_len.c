uint8_t ndp_msg_opt_route_prefix_len(struct ndp_msg *msg, int offset)
{
	struct __nd_opt_route_info *ri =
			ndp_msg_payload_opts_offset(msg, offset);

	return ri->nd_opt_ri_prefix_len;
}
