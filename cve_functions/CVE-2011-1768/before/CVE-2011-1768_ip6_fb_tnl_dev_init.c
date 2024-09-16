static void __net_init ip6_fb_tnl_dev_init(struct net_device *dev)
{
	struct ip6_tnl *t = netdev_priv(dev);
	struct net *net = dev_net(dev);
	struct ip6_tnl_net *ip6n = net_generic(net, ip6_tnl_net_id);

	ip6_tnl_dev_init_gen(dev);
	t->parms.proto = IPPROTO_IPV6;
	dev_hold(dev);
	ip6n->tnls_wc[0] = t;
}
