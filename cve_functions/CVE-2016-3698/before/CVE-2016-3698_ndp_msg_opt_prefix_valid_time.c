uint32_t ndp_msg_opt_prefix_valid_time(struct ndp_msg *msg, int offset)
{
	struct nd_opt_prefix_info *pi =
			ndp_msg_payload_opts_offset(msg, offset);

	return ntohl(pi->nd_opt_pi_valid_time);
}
