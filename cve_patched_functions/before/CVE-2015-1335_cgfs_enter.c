static inline bool cgfs_enter(void *hdata, pid_t pid)
{
	struct cgfs_data *d = hdata;
	struct cgroup_process_info *i;
	int ret;

	if (!d)
		return false;
	i = d->info;
	ret = lxc_cgroupfs_enter(i, pid, false);

	return ret == 0;
}
