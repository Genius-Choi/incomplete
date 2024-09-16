find_info_for_subsystem(struct cgroup_process_info *info, const char *subsystem)
{
	struct cgroup_process_info *info_ptr;
	for (info_ptr = info; info_ptr; info_ptr = info_ptr->next) {
		struct cgroup_hierarchy *h = info_ptr->hierarchy;
		if (lxc_string_in_array(subsystem, (const char **)h->subsystems))
			return info_ptr;
	}
	errno = ENOENT;
	return NULL;
}
