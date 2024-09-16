static struct net_device_stats *pegasus_netdev_stats(struct net_device *dev)
{
	return &((pegasus_t *) netdev_priv(dev))->stats;
}
