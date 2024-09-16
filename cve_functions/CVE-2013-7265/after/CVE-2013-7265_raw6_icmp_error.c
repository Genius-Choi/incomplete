void raw6_icmp_error(struct sk_buff *skb, int nexthdr,
		u8 type, u8 code, int inner_offset, __be32 info)
{
	struct sock *sk;
	int hash;
	const struct in6_addr *saddr, *daddr;
	struct net *net;

	hash = nexthdr & (RAW_HTABLE_SIZE - 1);

	read_lock(&raw_v6_hashinfo.lock);
	sk = sk_head(&raw_v6_hashinfo.ht[hash]);
	if (sk != NULL) {
		/* Note: ipv6_hdr(skb) != skb->data */
		const struct ipv6hdr *ip6h = (const struct ipv6hdr *)skb->data;
		saddr = &ip6h->saddr;
		daddr = &ip6h->daddr;
		net = dev_net(skb->dev);

		while ((sk = __raw_v6_lookup(net, sk, nexthdr, saddr, daddr,
						IP6CB(skb)->iif))) {
			rawv6_err(sk, skb, NULL, type, code,
					inner_offset, info);
			sk = sk_next(sk);
		}
	}
	read_unlock(&raw_v6_hashinfo.lock);
}
