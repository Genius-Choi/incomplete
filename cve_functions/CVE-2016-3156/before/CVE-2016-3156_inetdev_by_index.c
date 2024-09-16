struct in_device *inetdev_by_index(struct net *net, int ifindex)
{
	struct net_device *dev;
	struct in_device *in_dev = NULL;

	rcu_read_lock();
	dev = dev_get_by_index_rcu(net, ifindex);
	if (dev)
		in_dev = rcu_dereference_rtnl(dev->ip_ptr);
	rcu_read_unlock();
	return in_dev;
}
