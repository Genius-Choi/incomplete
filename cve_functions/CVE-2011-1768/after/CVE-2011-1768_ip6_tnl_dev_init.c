static void ip6_tnl_dev_init(struct net_device *dev)
{
	struct ip6_tnl *t = netdev_priv(dev);
	ip6_tnl_dev_init_gen(dev);
	ip6_tnl_link_config(t);
}
