static bool lxc_cgmanager_chmod(const char *controller,
		const char *cgroup_path, const char *file, int mode)
{
	if (cgmanager_chmod_sync(NULL, cgroup_manager, controller,
			cgroup_path, file, mode) != 0) {
		NihError *nerr;
		nerr = nih_error_get();
		ERROR("call to cgmanager_chmod_sync failed: %s", nerr->message);
		nih_free(nerr);
		return false;
	}
	return true;
}
