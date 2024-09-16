static __inline__ __sum16 tcp_v6_check(int len,
				   const struct in6_addr *saddr,
				   const struct in6_addr *daddr,
				   __wsum base)
{
	return csum_ipv6_magic(saddr, daddr, len, IPPROTO_TCP, base);
}
