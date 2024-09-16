int call_netdevice_notifiers(unsigned long val, struct net_device *dev)
{
	struct netdev_notifier_info info;

	return call_netdevice_notifiers_info(val, dev, &info);
}
