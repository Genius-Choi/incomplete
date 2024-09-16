static char *lxc_cgroup_find_abs_path(const char *subsystem, const char *group, bool should_be_writable, const char *suffix)
{
	struct cgroup_meta_data *meta_data;
	struct cgroup_hierarchy *h;
	struct cgroup_mount_point *mp;
	char *result;
	int saved_errno;

	meta_data = lxc_cgroup_load_meta();
	if (!meta_data)
		return NULL;

	h = lxc_cgroup_find_hierarchy(meta_data, subsystem);
	if (!h)
		goto out_error;

	mp = lxc_cgroup_find_mount_point(h, group, should_be_writable);
	if (!mp)
		goto out_error;

	result = cgroup_to_absolute_path(mp, group, suffix);
	if (!result)
		goto out_error;

	lxc_cgroup_put_meta(meta_data);
	return result;

out_error:
	saved_errno = errno;
	lxc_cgroup_put_meta(meta_data);
	errno = saved_errno;
	return NULL;
}
