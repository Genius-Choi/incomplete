static int  bond_release_and_destroy(struct net_device *bond_dev,
				     struct net_device *slave_dev)
{
	struct bonding *bond = netdev_priv(bond_dev);
	int ret;

	ret = bond_release(bond_dev, slave_dev);
	if ((ret == 0) && (bond->slave_cnt == 0)) {
		bond_dev->priv_flags |= IFF_DISABLE_NETPOLL;
		pr_info("%s: destroying bond %s.\n",
			bond_dev->name, bond_dev->name);
		unregister_netdevice(bond_dev);
	}
	return ret;
}
