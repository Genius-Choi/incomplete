unsigned char *ndp_msg_opt_tlladdr(struct ndp_msg *msg, int offset)
{
	unsigned char *opt_data = ndp_msg_payload_opts_offset(msg, offset);

	return &opt_data[2];
}
