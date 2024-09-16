static int sctp_v6_is_any(const union sctp_addr *addr)
{
	return ipv6_addr_any(&addr->v6.sin6_addr);
}
