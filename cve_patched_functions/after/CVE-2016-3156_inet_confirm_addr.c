__be32 inet_confirm_addr(struct net *net, struct in_device *in_dev,
			 __be32 dst, __be32 local, int scope)
{
	__be32 addr = 0;
	struct net_device *dev;

	if (in_dev)
		return confirm_addr_indev(in_dev, dst, local, scope);

	rcu_read_lock();
	for_each_netdev_rcu(net, dev) {
		in_dev = __in_dev_get_rcu(dev);
		if (in_dev) {
			addr = confirm_addr_indev(in_dev, dst, local, scope);
			if (addr)
				break;
		}
	}
	rcu_read_unlock();

	return addr;
}
