static int dn_device_event(struct notifier_block *this, unsigned long event,
			   void *ptr)
{
	struct net_device *dev = netdev_notifier_info_to_dev(ptr);

	if (!net_eq(dev_net(dev), &init_net))
		return NOTIFY_DONE;

	switch (event) {
	case NETDEV_UP:
		dn_dev_up(dev);
		break;
	case NETDEV_DOWN:
		dn_dev_down(dev);
		break;
	default:
		break;
	}

	return NOTIFY_DONE;
}
