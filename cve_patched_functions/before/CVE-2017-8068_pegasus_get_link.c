static u32 pegasus_get_link(struct net_device *dev)
{
	pegasus_t *pegasus = netdev_priv(dev);
	return mii_link_ok(&pegasus->mii);
}
