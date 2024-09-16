bool ndp_msg_opt_prefix_flag_on_link(struct ndp_msg *msg, int offset)
{
	struct nd_opt_prefix_info *pi =
			ndp_msg_payload_opts_offset(msg, offset);

	return pi->nd_opt_pi_flags_reserved & ND_OPT_PI_FLAG_ONLINK;
}
