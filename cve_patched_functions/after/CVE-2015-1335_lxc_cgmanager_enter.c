static bool lxc_cgmanager_enter(pid_t pid, const char *controller,
		const char *cgroup_path, bool abs)
{
	int ret;

	if (abs)
		ret = cgmanager_move_pid_abs_sync(NULL, cgroup_manager,
			controller, cgroup_path, pid);
	else
		ret = cgmanager_move_pid_sync(NULL, cgroup_manager,
			controller, cgroup_path, pid);
	if (ret != 0) {
		NihError *nerr;
		nerr = nih_error_get();
		ERROR("call to cgmanager_move_pid_%ssync failed: %s",
			abs ? "abs_" : "", nerr->message);
		nih_free(nerr);
		return false;
	}
	return true;
}
