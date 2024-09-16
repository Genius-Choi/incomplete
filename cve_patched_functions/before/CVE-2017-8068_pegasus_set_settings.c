pegasus_set_settings(struct net_device *dev, struct ethtool_cmd *ecmd)
{
	pegasus_t *pegasus = netdev_priv(dev);
	return mii_ethtool_sset(&pegasus->mii, ecmd);
}
