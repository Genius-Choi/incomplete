int bond_create(struct net *net, const char *name)
{
	struct net_device *bond_dev;
	int res;

	rtnl_lock();

	bond_dev = alloc_netdev_mq(sizeof(struct bonding),
				   name ? name : "bond%d",
				   bond_setup, tx_queues);
	if (!bond_dev) {
		pr_err("%s: eek! can't alloc netdev!\n", name);
		rtnl_unlock();
		return -ENOMEM;
	}

	dev_net_set(bond_dev, net);
	bond_dev->rtnl_link_ops = &bond_link_ops;

	res = register_netdevice(bond_dev);

	netif_carrier_off(bond_dev);

	rtnl_unlock();
	if (res < 0)
		bond_destructor(bond_dev);
	return res;
}
