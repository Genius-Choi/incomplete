static int hostap_disable_hostapd_sta(local_info_t *local, int rtnl_locked)
{
	struct net_device *dev = local->dev;

	printk(KERN_DEBUG "%s: disabling hostapd mode\n", dev->name);

	hostap_remove_interface(local->stadev, rtnl_locked, 1);
	local->stadev = NULL;

	return 0;
}
