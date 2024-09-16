static int vlan_ethtool_get_settings(struct net_device *dev,
				     struct ethtool_cmd *cmd)
{
	const struct vlan_dev_info *vlan = vlan_dev_info(dev);
	return dev_ethtool_get_settings(vlan->real_dev, cmd);
}
