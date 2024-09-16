static struct net_device *ip6mr_reg_vif(struct net *net, struct mr6_table *mrt)
{
	struct net_device *dev;
	char name[IFNAMSIZ];

	if (mrt->id == RT6_TABLE_DFLT)
		sprintf(name, "pim6reg");
	else
		sprintf(name, "pim6reg%u", mrt->id);

	dev = alloc_netdev(0, name, NET_NAME_UNKNOWN, reg_vif_setup);
	if (!dev)
		return NULL;

	dev_net_set(dev, net);

	if (register_netdevice(dev)) {
		free_netdev(dev);
		return NULL;
	}

	if (dev_open(dev))
		goto failure;

	dev_hold(dev);
	return dev;

failure:
	unregister_netdevice(dev);
	return NULL;
}
