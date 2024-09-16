pegasus_get_wol(struct net_device *dev, struct ethtool_wolinfo *wol)
{
	pegasus_t	*pegasus = netdev_priv(dev);

	wol->supported = WAKE_MAGIC | WAKE_PHY;
	wol->wolopts = pegasus->wolopts;
}
