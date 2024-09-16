static int ip6mr_device_event(struct notifier_block *this,
			      unsigned long event, void *ptr)
{
	struct net_device *dev = netdev_notifier_info_to_dev(ptr);
	struct net *net = dev_net(dev);
	struct mr6_table *mrt;
	struct mif_device *v;
	int ct;
	LIST_HEAD(list);

	if (event != NETDEV_UNREGISTER)
		return NOTIFY_DONE;

	ip6mr_for_each_table(mrt, net) {
		v = &mrt->vif6_table[0];
		for (ct = 0; ct < mrt->maxvif; ct++, v++) {
			if (v->dev == dev)
				mif6_delete(mrt, ct, &list);
		}
	}
	unregister_netdevice_many(&list);

	return NOTIFY_DONE;
}
