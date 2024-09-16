static void __tcp_v6_send_check(struct sk_buff *skb,
				const struct in6_addr *saddr, const struct in6_addr *daddr)
{
	struct tcphdr *th = tcp_hdr(skb);

	if (skb->ip_summed == CHECKSUM_PARTIAL) {
		th->check = ~tcp_v6_check(skb->len, saddr, daddr, 0);
		skb->csum_start = skb_transport_header(skb) - skb->head;
		skb->csum_offset = offsetof(struct tcphdr, check);
	} else {
		th->check = tcp_v6_check(skb->len, saddr, daddr,
					 csum_partial(th, th->doff << 2,
						      skb->csum));
	}
}
