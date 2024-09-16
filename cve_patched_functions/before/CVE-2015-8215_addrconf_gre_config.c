static void addrconf_gre_config(struct net_device *dev)
{
	struct inet6_dev *idev;

	ASSERT_RTNL();

	idev = ipv6_find_idev(dev);
	if (idev == NULL) {
		pr_debug("%s: add_dev failed\n", __func__);
		return;
	}

	addrconf_addr_gen(idev, true);
}
