static struct neighbour *ipv4_neigh_lookup(const struct dst_entry *dst,
					   struct sk_buff *skb,
					   const void *daddr)
{
	struct net_device *dev = dst->dev;
	const __be32 *pkey = daddr;
	const struct rtable *rt;
	struct neighbour *n;

	rt = (const struct rtable *) dst;
	if (rt->rt_gateway)
		pkey = (const __be32 *) &rt->rt_gateway;
	else if (skb)
		pkey = &ip_hdr(skb)->daddr;

	n = __ipv4_neigh_lookup(dev, *(__force u32 *)pkey);
	if (n)
		return n;
	return neigh_create(&arp_tbl, pkey, dev);
}
