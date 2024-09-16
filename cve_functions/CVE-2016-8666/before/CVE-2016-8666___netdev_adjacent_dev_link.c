static int __netdev_adjacent_dev_link(struct net_device *dev,
				      struct net_device *upper_dev)
{
	return __netdev_adjacent_dev_link_lists(dev, upper_dev,
						&dev->all_adj_list.upper,
						&upper_dev->all_adj_list.lower,
						NULL, false);
}
