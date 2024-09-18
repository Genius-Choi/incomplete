static int lxc_cgroupfs_enter(struct cgroup_process_info *info, pid_t pid, bool enter_sub)
{
	char pid_buf[32];
	char *cgroup_tasks_fn;
	int r;
	struct cgroup_process_info *info_ptr;

	snprintf(pid_buf, 32, "%lu", (unsigned long)pid);
	for (info_ptr = info; info_ptr; info_ptr = info_ptr->next) {
		char *cgroup_path = (enter_sub && info_ptr->cgroup_path_sub) ?
			info_ptr->cgroup_path_sub :
			info_ptr->cgroup_path;

		if (!info_ptr->designated_mount_point) {
			info_ptr->designated_mount_point = lxc_cgroup_find_mount_point(info_ptr->hierarchy, cgroup_path, true);
			if (!info_ptr->designated_mount_point) {
				SYSERROR("Could not add pid %lu to cgroup %s: internal error (couldn't find any writable mountpoint to cgroup filesystem)", (unsigned long)pid, cgroup_path);
				return -1;
			}
		}

		cgroup_tasks_fn = cgroup_to_absolute_path(info_ptr->designated_mount_point, cgroup_path, "/tasks");
		if (!cgroup_tasks_fn) {
			SYSERROR("Could not add pid %lu to cgroup %s: internal error", (unsigned long)pid, cgroup_path);
			return -1;
		}

		r = lxc_write_to_file(cgroup_tasks_fn, pid_buf, strlen(pid_buf), false);
		free(cgroup_tasks_fn);
		if (r < 0) {
			SYSERROR("Could not add pid %lu to cgroup %s: internal error", (unsigned long)pid, cgroup_path);
			return -1;
		}
	}

	return 0;
}
