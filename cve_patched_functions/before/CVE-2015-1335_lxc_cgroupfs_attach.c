static bool lxc_cgroupfs_attach(const char *name, const char *lxcpath, pid_t pid)
{
	struct cgroup_meta_data *meta_data;
	struct cgroup_process_info *container_info;
	int ret;

	meta_data = lxc_cgroup_load_meta();
	if (!meta_data) {
		ERROR("could not move attached process %d to cgroup of container", pid);
		return false;
	}

	container_info = lxc_cgroup_get_container_info(name, lxcpath, meta_data);
	lxc_cgroup_put_meta(meta_data);
	if (!container_info) {
		ERROR("could not move attached process %d to cgroup of container", pid);
		return false;
	}

	ret = lxc_cgroupfs_enter(container_info, pid, false);
	lxc_cgroup_process_info_free(container_info);
	if (ret < 0) {
		ERROR("could not move attached process %d to cgroup of container", pid);
		return false;
	}
	return true;
}
