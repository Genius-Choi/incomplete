static u32 vlan_dev_fix_features(struct net_device *dev, u32 features)
{
	struct net_device *real_dev = vlan_dev_info(dev)->real_dev;
	u32 old_features = features;

	features &= real_dev->features;
	features &= real_dev->vlan_features;

	features |= old_features & NETIF_F_SOFT_FEATURES;

	if (dev_ethtool_get_rx_csum(real_dev))
		features |= NETIF_F_RXCSUM;
	features |= NETIF_F_LLTX;

	return features;
}
