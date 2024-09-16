bool ipv6_chk_custom_prefix(const struct in6_addr *addr,
	const unsigned int prefix_len, struct net_device *dev)
{
	struct inet6_dev *idev;
	struct inet6_ifaddr *ifa;
	bool ret = false;

	rcu_read_lock();
	idev = __in6_dev_get(dev);
	if (idev) {
		read_lock_bh(&idev->lock);
		list_for_each_entry(ifa, &idev->addr_list, if_list) {
			ret = ipv6_prefix_equal(addr, &ifa->addr, prefix_len);
			if (ret)
				break;
		}
		read_unlock_bh(&idev->lock);
	}
	rcu_read_unlock();

	return ret;
}
