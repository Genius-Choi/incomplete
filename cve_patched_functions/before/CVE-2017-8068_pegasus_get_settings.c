pegasus_get_settings(struct net_device *dev, struct ethtool_cmd *ecmd)
{
	pegasus_t *pegasus;

	pegasus = netdev_priv(dev);
	mii_ethtool_gset(&pegasus->mii, ecmd);
	return 0;
}
