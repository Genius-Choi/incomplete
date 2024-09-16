static int udp4_gro_complete(struct sk_buff *skb, int nhoff)
{
	const struct iphdr *iph = ip_hdr(skb);
	struct udphdr *uh = (struct udphdr *)(skb->data + nhoff);

	if (uh->check) {
		skb_shinfo(skb)->gso_type |= SKB_GSO_UDP_TUNNEL_CSUM;
		uh->check = ~udp_v4_check(skb->len - nhoff, iph->saddr,
					  iph->daddr, 0);
	} else {
		skb_shinfo(skb)->gso_type |= SKB_GSO_UDP_TUNNEL;
	}

	return udp_gro_complete(skb, nhoff);
}
