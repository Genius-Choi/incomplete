static struct cgroup_meta_data *lxc_cgroup_load_meta()
{
	const char *cgroup_use = NULL;
	char **cgroup_use_list = NULL;
	struct cgroup_meta_data *md = NULL;
	int saved_errno;

	errno = 0;
	cgroup_use = lxc_global_config_value("lxc.cgroup.use");
	if (!cgroup_use && errno != 0)
		return NULL;
	if (cgroup_use) {
		cgroup_use_list = lxc_string_split_and_trim(cgroup_use, ',');
		if (!cgroup_use_list)
			return NULL;
	}

	md = lxc_cgroup_load_meta2((const char **)cgroup_use_list);
	saved_errno = errno;
	lxc_free_array((void **)cgroup_use_list, free);
	errno = saved_errno;
	return md;
}
