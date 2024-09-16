int hostap_set_hostapd_sta(local_info_t *local, int val, int rtnl_locked)
{
	int ret;

	if (val < 0 || val > 1)
		return -EINVAL;

	if (local->hostapd_sta == val)
		return 0;

	if (val) {
		ret = hostap_enable_hostapd_sta(local, rtnl_locked);
		if (ret == 0)
			local->hostapd_sta = 1;
	} else {
		local->hostapd_sta = 0;
		ret = hostap_disable_hostapd_sta(local, rtnl_locked);
		if (ret != 0)
			local->hostapd_sta = 1;
	}


	return ret;
}
