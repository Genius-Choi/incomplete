static int hostap_enable_hostapd(local_info_t *local, int rtnl_locked)
{
	struct net_device *dev = local->dev;

	if (local->apdev)
		return -EEXIST;

	printk(KERN_DEBUG "%s: enabling hostapd mode\n", dev->name);

	local->apdev = hostap_add_interface(local, HOSTAP_INTERFACE_AP,
					    rtnl_locked, local->ddev->name,
					    "ap");
	if (local->apdev == NULL)
		return -ENOMEM;

	return 0;
}
