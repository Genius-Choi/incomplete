static bool ip6_datagram_support_cmsg(struct sk_buff *skb,
				      struct sock_exterr_skb *serr)
{
	if (serr->ee.ee_origin == SO_EE_ORIGIN_ICMP ||
	    serr->ee.ee_origin == SO_EE_ORIGIN_ICMP6)
		return true;

	if (serr->ee.ee_origin == SO_EE_ORIGIN_LOCAL)
		return false;

	if (!skb->dev)
		return false;

	if (skb->protocol == htons(ETH_P_IPV6))
		IP6CB(skb)->iif = skb->dev->ifindex;
	else
		PKTINFO_SKB_CB(skb)->ipi_ifindex = skb->dev->ifindex;

	return true;
}
