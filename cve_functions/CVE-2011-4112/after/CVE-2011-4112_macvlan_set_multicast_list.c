static void macvlan_set_multicast_list(struct net_device *dev)
{
	struct macvlan_dev *vlan = netdev_priv(dev);

	dev_mc_sync(vlan->lowerdev, dev);
}
