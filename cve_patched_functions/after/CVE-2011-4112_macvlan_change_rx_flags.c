static void macvlan_change_rx_flags(struct net_device *dev, int change)
{
	struct macvlan_dev *vlan = netdev_priv(dev);
	struct net_device *lowerdev = vlan->lowerdev;

	if (change & IFF_ALLMULTI)
		dev_set_allmulti(lowerdev, dev->flags & IFF_ALLMULTI ? 1 : -1);
}
