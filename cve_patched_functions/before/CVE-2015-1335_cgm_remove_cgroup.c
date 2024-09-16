static void cgm_remove_cgroup(const char *controller, const char *path)
{
	int existed;
	if ( cgmanager_remove_sync(NULL, cgroup_manager, controller,
				   path, CG_REMOVE_RECURSIVE, &existed) != 0) {
		NihError *nerr;
		nerr = nih_error_get();
		ERROR("call to cgmanager_remove_sync failed: %s", nerr->message);
		nih_free(nerr);
		ERROR("Error removing %s:%s", controller, path);
	}
	if (existed == -1)
		INFO("cgroup removal attempt: %s:%s did not exist", controller, path);
}
