static void __netdev_adjacent_dev_unlink(struct net_device *dev,
					 struct net_device *upper_dev)
{
	__netdev_adjacent_dev_unlink_lists(dev, upper_dev,
					   &dev->all_adj_list.upper,
					   &upper_dev->all_adj_list.lower);
}
