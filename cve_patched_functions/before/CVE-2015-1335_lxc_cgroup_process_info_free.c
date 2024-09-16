void lxc_cgroup_process_info_free(struct cgroup_process_info *info)
{
	struct cgroup_process_info *next;
	if (!info)
		return;
	next = info->next;
	lxc_cgroup_put_meta(info->meta_ref);
	free(info->cgroup_path);
	free(info->cgroup_path_sub);
	lxc_free_array((void **)info->created_paths, free);
	free(info);
	lxc_cgroup_process_info_free(next);
}
