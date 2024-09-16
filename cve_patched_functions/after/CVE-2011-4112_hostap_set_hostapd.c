int hostap_set_hostapd(local_info_t *local, int val, int rtnl_locked)
{
	int ret;

	if (val < 0 || val > 1)
		return -EINVAL;

	if (local->hostapd == val)
		return 0;

	if (val) {
		ret = hostap_enable_hostapd(local, rtnl_locked);
		if (ret == 0)
			local->hostapd = 1;
	} else {
		local->hostapd = 0;
		ret = hostap_disable_hostapd(local, rtnl_locked);
		if (ret != 0)
			local->hostapd = 1;
	}

	return ret;
}
