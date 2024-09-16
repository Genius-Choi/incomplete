static struct cgroup_process_info *lxc_cgroup_process_info_get_self(struct cgroup_meta_data *meta)
{
	struct cgroup_process_info *i;
	i = lxc_cgroup_process_info_getx("/proc/self/cgroup", meta);
	if (!i)
		i = lxc_cgroup_process_info_get(getpid(), meta);
	return i;
}
