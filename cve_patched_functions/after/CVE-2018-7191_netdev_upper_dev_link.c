int netdev_upper_dev_link(struct net_device *dev,
			  struct net_device *upper_dev)
{
	return __netdev_upper_dev_link(dev, upper_dev, false, NULL, NULL);
}
