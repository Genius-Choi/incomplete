static const char *cgfs_get_cgroup(void *hdata, const char *subsystem)
{
	struct cgfs_data *d = hdata;

	if (!d)
		return NULL;
	return lxc_cgroup_get_hierarchy_path_data(subsystem, d);
}
