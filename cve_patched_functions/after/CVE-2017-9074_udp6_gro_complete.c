static int udp6_gro_complete(struct sk_buff *skb, int nhoff)
{
	const struct ipv6hdr *ipv6h = ipv6_hdr(skb);
	struct udphdr *uh = (struct udphdr *)(skb->data + nhoff);

	if (uh->check) {
		skb_shinfo(skb)->gso_type |= SKB_GSO_UDP_TUNNEL_CSUM;
		uh->check = ~udp_v6_check(skb->len - nhoff, &ipv6h->saddr,
					  &ipv6h->daddr, 0);
	} else {
		skb_shinfo(skb)->gso_type |= SKB_GSO_UDP_TUNNEL;
	}

	return udp_gro_complete(skb, nhoff, udp6_lib_lookup_skb);
}
