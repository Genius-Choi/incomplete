static inline void ipip_ecn_decapsulate(const struct iphdr *outer_iph,
					struct sk_buff *skb)
{
	struct iphdr *inner_iph = ip_hdr(skb);

	if (INET_ECN_is_ce(outer_iph->tos))
		IP_ECN_set_ce(inner_iph);
}
