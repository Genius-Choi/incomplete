static char *lxc_cgroup_get_hierarchy_abs_path_data(const char *subsystem, struct cgfs_data *d)
{
	struct cgroup_process_info *info = d->info;
	struct cgroup_mount_point *mp = NULL;

	info = find_info_for_subsystem(info, subsystem);
	if (!info)
		return NULL;
	if (info->designated_mount_point) {
		mp = info->designated_mount_point;
	} else {
		mp = lxc_cgroup_find_mount_point(info->hierarchy, info->cgroup_path, true);
		if (!mp)
			return NULL;
	}
	return cgroup_to_absolute_path(mp, info->cgroup_path, NULL);
}
