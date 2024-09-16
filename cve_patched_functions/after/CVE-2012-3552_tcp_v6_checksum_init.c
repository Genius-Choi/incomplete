static __sum16 tcp_v6_checksum_init(struct sk_buff *skb)
{
	if (skb->ip_summed == CHECKSUM_COMPLETE) {
		if (!tcp_v6_check(skb->len, &ipv6_hdr(skb)->saddr,
				  &ipv6_hdr(skb)->daddr, skb->csum)) {
			skb->ip_summed = CHECKSUM_UNNECESSARY;
			return 0;
		}
	}

	skb->csum = ~csum_unfold(tcp_v6_check(skb->len,
					      &ipv6_hdr(skb)->saddr,
					      &ipv6_hdr(skb)->daddr, 0));

	if (skb->len <= 76) {
		return __skb_checksum_complete(skb);
	}
	return 0;
}
