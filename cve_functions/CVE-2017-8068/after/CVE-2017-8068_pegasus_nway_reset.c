static int pegasus_nway_reset(struct net_device *dev)
{
	pegasus_t *pegasus = netdev_priv(dev);
	return mii_nway_restart(&pegasus->mii);
}
