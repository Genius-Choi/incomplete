static char *lxc_cgroup_get_hierarchy_path_data(const char *subsystem, struct cgfs_data *d)
{
	struct cgroup_process_info *info = d->info;
	info = find_info_for_subsystem(info, subsystem);
	if (!info)
		return NULL;
	return info->cgroup_path;
}
