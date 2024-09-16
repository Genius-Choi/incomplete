uint32_t ndp_msg_opt_rdnss_lifetime(struct ndp_msg *msg, int offset)
{
	struct __nd_opt_rdnss *rdnss =
			ndp_msg_payload_opts_offset(msg, offset);

	return ntohl(rdnss->nd_opt_rdnss_lifetime);
}
