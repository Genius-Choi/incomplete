static int call_netdevice_notifiers_info(unsigned long val,
					 struct net_device *dev,
					 struct netdev_notifier_info *info)
{
	ASSERT_RTNL();
	netdev_notifier_info_init(info, dev);
	return raw_notifier_call_chain(&netdev_chain, val, info);
}
