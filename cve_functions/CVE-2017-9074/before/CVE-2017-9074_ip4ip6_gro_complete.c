static int ip4ip6_gro_complete(struct sk_buff *skb, int nhoff)
{
	skb->encapsulation = 1;
	skb_shinfo(skb)->gso_type |= SKB_GSO_IPXIP6;
	return inet_gro_complete(skb, nhoff);
}
