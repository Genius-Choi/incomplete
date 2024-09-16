static inline void free_abs_cgroup(char *cgroup)
{
	if (!cgroup)
		return;
	if (abs_cgroup_supported())
		nih_free(cgroup);
	else
		free(cgroup);
}
