static int macvlan_ethtool_get_settings(struct net_device *dev,
					struct ethtool_cmd *cmd)
{
	const struct macvlan_dev *vlan = netdev_priv(dev);
	return dev_ethtool_get_settings(vlan->lowerdev, cmd);
}
