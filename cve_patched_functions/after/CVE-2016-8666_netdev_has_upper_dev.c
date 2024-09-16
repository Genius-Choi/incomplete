bool netdev_has_upper_dev(struct net_device *dev,
			  struct net_device *upper_dev)
{
	ASSERT_RTNL();

	return __netdev_find_adj(upper_dev, &dev->all_adj_list.upper);
}
