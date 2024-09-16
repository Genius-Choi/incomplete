static struct cgroup_process_info *lxc_cgroup_process_info_get(pid_t pid, struct cgroup_meta_data *meta)
{
	char pid_buf[32];
	snprintf(pid_buf, 32, "/proc/%lu/cgroup", (unsigned long)pid);
	return lxc_cgroup_process_info_getx(pid_buf, meta);
}
