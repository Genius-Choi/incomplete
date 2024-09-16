static bool cgfs_unfreeze(void *hdata)
{
	struct cgfs_data *d = hdata;
	char *cgabspath, *cgrelpath;
	int ret;

	if (!d)
		return false;

	cgrelpath = lxc_cgroup_get_hierarchy_path_data("freezer", d);
	cgabspath = lxc_cgroup_find_abs_path("freezer", cgrelpath, true, NULL);
	if (!cgabspath)
		return false;

	ret = do_cgroup_set(cgabspath, "freezer.state", "THAWED");
	free(cgabspath);
	return ret == 0;
}
