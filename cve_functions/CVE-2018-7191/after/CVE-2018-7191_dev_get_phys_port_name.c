int dev_get_phys_port_name(struct net_device *dev,
			   char *name, size_t len)
{
	const struct net_device_ops *ops = dev->netdev_ops;

	if (!ops->ndo_get_phys_port_name)
		return -EOPNOTSUPP;
	return ops->ndo_get_phys_port_name(dev, name, len);
}
