static __u32 secure_tcp_syn_cookie(const struct in6_addr *saddr,
				   const struct in6_addr *daddr,
				   __be16 sport, __be16 dport, __u32 sseq,
				   __u32 data)
{
	u32 count = tcp_cookie_time();
	return (cookie_hash(saddr, daddr, sport, dport, 0, 0) +
		sseq + (count << COOKIEBITS) +
		((cookie_hash(saddr, daddr, sport, dport, count, 1) + data)
		& COOKIEMASK));
}
