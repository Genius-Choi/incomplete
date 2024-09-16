static inline int sctp_v6_addr_match_len(union sctp_addr *s1,
					 union sctp_addr *s2)
{
	return ipv6_addr_diff(&s1->v6.sin6_addr, &s2->v6.sin6_addr);
}
