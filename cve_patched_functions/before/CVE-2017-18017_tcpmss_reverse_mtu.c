static u_int32_t tcpmss_reverse_mtu(struct net *net,
				    const struct sk_buff *skb,
				    unsigned int family)
{
	struct flowi fl;
	const struct nf_afinfo *ai;
	struct rtable *rt = NULL;
	u_int32_t mtu     = ~0U;

	if (family == PF_INET) {
		struct flowi4 *fl4 = &fl.u.ip4;
		memset(fl4, 0, sizeof(*fl4));
		fl4->daddr = ip_hdr(skb)->saddr;
	} else {
		struct flowi6 *fl6 = &fl.u.ip6;

		memset(fl6, 0, sizeof(*fl6));
		fl6->daddr = ipv6_hdr(skb)->saddr;
	}
	rcu_read_lock();
	ai = nf_get_afinfo(family);
	if (ai != NULL)
		ai->route(net, (struct dst_entry **)&rt, &fl, false);
	rcu_read_unlock();

	if (rt != NULL) {
		mtu = dst_mtu(&rt->dst);
		dst_release(&rt->dst);
	}
	return mtu;
}
