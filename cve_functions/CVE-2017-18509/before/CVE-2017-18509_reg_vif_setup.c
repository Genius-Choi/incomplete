static void reg_vif_setup(struct net_device *dev)
{
	dev->type		= ARPHRD_PIMREG;
	dev->mtu		= 1500 - sizeof(struct ipv6hdr) - 8;
	dev->flags		= IFF_NOARP;
	dev->netdev_ops		= &reg_vif_netdev_ops;
	dev->destructor		= free_netdev;
	dev->features		|= NETIF_F_NETNS_LOCAL;
}
