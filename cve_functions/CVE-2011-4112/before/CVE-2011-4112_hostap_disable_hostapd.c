static int hostap_disable_hostapd(local_info_t *local, int rtnl_locked)
{
	struct net_device *dev = local->dev;

	printk(KERN_DEBUG "%s: disabling hostapd mode\n", dev->name);

	hostap_remove_interface(local->apdev, rtnl_locked, 1);
	local->apdev = NULL;

	return 0;
}
