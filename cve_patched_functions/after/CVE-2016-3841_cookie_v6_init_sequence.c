__u32 cookie_v6_init_sequence(const struct sk_buff *skb, __u16 *mssp)
{
	const struct ipv6hdr *iph = ipv6_hdr(skb);
	const struct tcphdr *th = tcp_hdr(skb);

	return __cookie_v6_init_sequence(iph, th, mssp);
}
