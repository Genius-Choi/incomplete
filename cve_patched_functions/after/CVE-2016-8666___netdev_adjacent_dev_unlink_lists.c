static void __netdev_adjacent_dev_unlink_lists(struct net_device *dev,
					       struct net_device *upper_dev,
					       struct list_head *up_list,
					       struct list_head *down_list)
{
	__netdev_adjacent_dev_remove(dev, upper_dev, up_list);
	__netdev_adjacent_dev_remove(upper_dev, dev, down_list);
}
