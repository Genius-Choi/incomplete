static inline __sum16 dccp_v6_csum_finish(struct sk_buff *skb,
				      const struct in6_addr *saddr,
				      const struct in6_addr *daddr)
{
	return csum_ipv6_magic(saddr, daddr, skb->len, IPPROTO_DCCP, skb->csum);
}
