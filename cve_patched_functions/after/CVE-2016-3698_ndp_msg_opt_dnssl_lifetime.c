uint32_t ndp_msg_opt_dnssl_lifetime(struct ndp_msg *msg, int offset)
{
	struct __nd_opt_dnssl *dnssl =
			ndp_msg_payload_opts_offset(msg, offset);

	return ntohl(dnssl->nd_opt_dnssl_lifetime);
}
