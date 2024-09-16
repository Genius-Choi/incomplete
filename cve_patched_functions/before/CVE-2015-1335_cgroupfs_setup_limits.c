static bool cgroupfs_setup_limits(void *hdata, struct lxc_list *cgroup_conf,
				  bool with_devices)
{
	struct cgfs_data *d = hdata;

	if (!d)
		return false;
	return do_setup_cgroup_limits(d, cgroup_conf, with_devices) == 0;
}
