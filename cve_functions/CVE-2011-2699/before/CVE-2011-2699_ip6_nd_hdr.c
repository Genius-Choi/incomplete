int ip6_nd_hdr(struct sock *sk, struct sk_buff *skb, struct net_device *dev,
	       const struct in6_addr *saddr, const struct in6_addr *daddr,
	       int proto, int len)
{
	struct ipv6_pinfo *np = inet6_sk(sk);
	struct ipv6hdr *hdr;

	skb->protocol = htons(ETH_P_IPV6);
	skb->dev = dev;

	skb_reset_network_header(skb);
	skb_put(skb, sizeof(struct ipv6hdr));
	hdr = ipv6_hdr(skb);

	*(__be32*)hdr = htonl(0x60000000);

	hdr->payload_len = htons(len);
	hdr->nexthdr = proto;
	hdr->hop_limit = np->hop_limit;

	ipv6_addr_copy(&hdr->saddr, saddr);
	ipv6_addr_copy(&hdr->daddr, daddr);

	return 0;
}
