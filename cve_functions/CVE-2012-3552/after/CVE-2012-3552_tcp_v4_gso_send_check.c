int tcp_v4_gso_send_check(struct sk_buff *skb)
{
	const struct iphdr *iph;
	struct tcphdr *th;

	if (!pskb_may_pull(skb, sizeof(*th)))
		return -EINVAL;

	iph = ip_hdr(skb);
	th = tcp_hdr(skb);

	th->check = 0;
	skb->ip_summed = CHECKSUM_PARTIAL;
	__tcp_v4_send_check(skb, iph->saddr, iph->daddr);
	return 0;
}
