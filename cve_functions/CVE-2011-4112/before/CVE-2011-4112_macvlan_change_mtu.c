static int macvlan_change_mtu(struct net_device *dev, int new_mtu)
{
	struct macvlan_dev *vlan = netdev_priv(dev);

	if (new_mtu < 68 || vlan->lowerdev->mtu < new_mtu)
		return -EINVAL;
	dev->mtu = new_mtu;
	return 0;
}
