static bool ipv6_hop_ra(struct sk_buff *skb, int optoff)
{
	const unsigned char *nh = skb_network_header(skb);

	if (nh[optoff + 1] == 2) {
		IP6CB(skb)->flags |= IP6SKB_ROUTERALERT;
		memcpy(&IP6CB(skb)->ra, nh + optoff + 2, sizeof(IP6CB(skb)->ra));
		return true;
	}
	net_dbg_ratelimited("ipv6_hop_ra: wrong RA length %d\n",
			    nh[optoff + 1]);
	kfree_skb(skb);
	return false;
}
