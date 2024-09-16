static int __netdev_adjacent_dev_link_neighbour(struct net_device *dev,
						struct net_device *upper_dev,
						void *private, bool master)
{
	int ret = __netdev_adjacent_dev_link(dev, upper_dev);

	if (ret)
		return ret;

	ret = __netdev_adjacent_dev_link_lists(dev, upper_dev,
					       &dev->adj_list.upper,
					       &upper_dev->adj_list.lower,
					       private, master);
	if (ret) {
		__netdev_adjacent_dev_unlink(dev, upper_dev);
		return ret;
	}

	return 0;
}
