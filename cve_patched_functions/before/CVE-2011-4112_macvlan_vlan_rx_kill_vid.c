static void macvlan_vlan_rx_kill_vid(struct net_device *dev,
				     unsigned short vid)
{
	struct macvlan_dev *vlan = netdev_priv(dev);
	struct net_device *lowerdev = vlan->lowerdev;
	const struct net_device_ops *ops = lowerdev->netdev_ops;

	if (ops->ndo_vlan_rx_kill_vid)
		ops->ndo_vlan_rx_kill_vid(lowerdev, vid);
}
