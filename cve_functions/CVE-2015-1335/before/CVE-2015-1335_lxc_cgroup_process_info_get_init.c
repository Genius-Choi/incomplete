static struct cgroup_process_info *lxc_cgroup_process_info_get_init(struct cgroup_meta_data *meta)
{
	return lxc_cgroup_process_info_get(1, meta);
}
