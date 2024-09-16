static int __fib_validate_source(struct sk_buff *skb, __be32 src, __be32 dst,
				 u8 tos, int oif, struct net_device *dev,
				 int rpf, struct in_device *idev, u32 *itag)
{
	int ret, no_addr;
	struct fib_result res;
	struct flowi4 fl4;
	struct net *net;
	bool dev_match;

	fl4.flowi4_oif = 0;
	fl4.flowi4_iif = l3mdev_master_ifindex_rcu(dev);
	if (!fl4.flowi4_iif)
		fl4.flowi4_iif = oif ? : LOOPBACK_IFINDEX;
	fl4.daddr = src;
	fl4.saddr = dst;
	fl4.flowi4_tos = tos;
	fl4.flowi4_scope = RT_SCOPE_UNIVERSE;
	fl4.flowi4_tun_key.tun_id = 0;
	fl4.flowi4_flags = 0;

	no_addr = idev->ifa_list == NULL;

	fl4.flowi4_mark = IN_DEV_SRC_VMARK(idev) ? skb->mark : 0;

	trace_fib_validate_source(dev, &fl4);

	net = dev_net(dev);
	if (fib_lookup(net, &fl4, &res, 0))
		goto last_resort;
	if (res.type != RTN_UNICAST &&
	    (res.type != RTN_LOCAL || !IN_DEV_ACCEPT_LOCAL(idev)))
		goto e_inval;
	if (!rpf && !fib_num_tclassid_users(dev_net(dev)) &&
	    (dev->ifindex != oif || !IN_DEV_TX_REDIRECTS(idev)))
		goto last_resort;
	fib_combine_itag(itag, &res);
	dev_match = false;

#ifdef CONFIG_IP_ROUTE_MULTIPATH
	for (ret = 0; ret < res.fi->fib_nhs; ret++) {
		struct fib_nh *nh = &res.fi->fib_nh[ret];

		if (nh->nh_dev == dev) {
			dev_match = true;
			break;
		} else if (l3mdev_master_ifindex_rcu(nh->nh_dev) == dev->ifindex) {
			dev_match = true;
			break;
		}
	}
#else
	if (FIB_RES_DEV(res) == dev)
		dev_match = true;
#endif
	if (dev_match) {
		ret = FIB_RES_NH(res).nh_scope >= RT_SCOPE_HOST;
		return ret;
	}
	if (no_addr)
		goto last_resort;
	if (rpf == 1)
		goto e_rpf;
	fl4.flowi4_oif = dev->ifindex;

	ret = 0;
	if (fib_lookup(net, &fl4, &res, FIB_LOOKUP_IGNORE_LINKSTATE) == 0) {
		if (res.type == RTN_UNICAST)
			ret = FIB_RES_NH(res).nh_scope >= RT_SCOPE_HOST;
	}
	return ret;

last_resort:
	if (rpf)
		goto e_rpf;
	*itag = 0;
	return 0;

e_inval:
	return -EINVAL;
e_rpf:
	return -EXDEV;
}
