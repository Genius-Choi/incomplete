static int hostap_enable_hostapd_sta(local_info_t *local, int rtnl_locked)
{
	struct net_device *dev = local->dev;

	if (local->stadev)
		return -EEXIST;

	printk(KERN_DEBUG "%s: enabling hostapd STA mode\n", dev->name);

	local->stadev = hostap_add_interface(local, HOSTAP_INTERFACE_STA,
					     rtnl_locked, local->ddev->name,
					     "sta");
	if (local->stadev == NULL)
		return -ENOMEM;

	return 0;
}
