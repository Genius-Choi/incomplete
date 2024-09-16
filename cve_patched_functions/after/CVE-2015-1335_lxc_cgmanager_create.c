static bool lxc_cgmanager_create(const char *controller, const char *cgroup_path, int32_t *existed)
{
	bool ret = true;
	if ( cgmanager_create_sync(NULL, cgroup_manager, controller,
				       cgroup_path, existed) != 0) {
		NihError *nerr;
		nerr = nih_error_get();
		ERROR("call to cgmanager_create_sync failed: %s", nerr->message);
		nih_free(nerr);
		ERROR("Failed to create %s:%s", controller, cgroup_path);
		ret = false;
	}

	return ret;
}
