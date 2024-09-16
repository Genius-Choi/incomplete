static int inet6_addr_del(struct net *net, int ifindex, u32 ifa_flags,
			  const struct in6_addr *pfx, unsigned int plen)
{
	struct inet6_ifaddr *ifp;
	struct inet6_dev *idev;
	struct net_device *dev;

	if (plen > 128)
		return -EINVAL;

	dev = __dev_get_by_index(net, ifindex);
	if (!dev)
		return -ENODEV;

	idev = __in6_dev_get(dev);
	if (idev == NULL)
		return -ENXIO;

	read_lock_bh(&idev->lock);
	list_for_each_entry(ifp, &idev->addr_list, if_list) {
		if (ifp->prefix_len == plen &&
		    ipv6_addr_equal(pfx, &ifp->addr)) {
			in6_ifa_hold(ifp);
			read_unlock_bh(&idev->lock);

			if (!(ifp->flags & IFA_F_TEMPORARY) &&
			    (ifa_flags & IFA_F_MANAGETEMPADDR))
				manage_tempaddrs(idev, ifp, 0, 0, false,
						 jiffies);
			ipv6_del_addr(ifp);
			addrconf_verify_rtnl();
			return 0;
		}
	}
	read_unlock_bh(&idev->lock);
	return -EADDRNOTAVAIL;
}
