int udp4_ufo_send_check(struct sk_buff *skb)
{
	const struct iphdr *iph;
	struct udphdr *uh;

	if (!pskb_may_pull(skb, sizeof(*uh)))
		return -EINVAL;

	iph = ip_hdr(skb);
	uh = udp_hdr(skb);

	uh->check = ~csum_tcpudp_magic(iph->saddr, iph->daddr, skb->len,
				       IPPROTO_UDP, 0);
	skb->csum_start = skb_transport_header(skb) - skb->head;
	skb->csum_offset = offsetof(struct udphdr, check);
	skb->ip_summed = CHECKSUM_PARTIAL;
	return 0;
}
