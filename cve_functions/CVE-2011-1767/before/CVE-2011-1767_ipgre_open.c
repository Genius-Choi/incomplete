static int ipgre_open(struct net_device *dev)
{
	struct ip_tunnel *t = netdev_priv(dev);

	if (ipv4_is_multicast(t->parms.iph.daddr)) {
		struct flowi fl = { .oif = t->parms.link,
				    .nl_u = { .ip4_u =
					      { .daddr = t->parms.iph.daddr,
						.saddr = t->parms.iph.saddr,
						.tos = RT_TOS(t->parms.iph.tos) } },
				    .proto = IPPROTO_GRE };
		struct rtable *rt;
		if (ip_route_output_key(dev_net(dev), &rt, &fl))
			return -EADDRNOTAVAIL;
		dev = rt->u.dst.dev;
		ip_rt_put(rt);
		if (__in_dev_get_rtnl(dev) == NULL)
			return -EADDRNOTAVAIL;
		t->mlink = dev->ifindex;
		ip_mc_inc_group(__in_dev_get_rtnl(dev), t->parms.iph.daddr);
	}
	return 0;
}
