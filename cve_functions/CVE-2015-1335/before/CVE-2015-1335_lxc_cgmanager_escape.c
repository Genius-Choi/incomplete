static bool lxc_cgmanager_escape(void)
{
	bool ret = true;
	pid_t me = getpid();
	char **slist = subsystems;
	int i;

	if (cgm_all_controllers_same)
		slist = subsystems_inone;

	for (i = 0; slist[i]; i++) {
		if (cgmanager_move_pid_abs_sync(NULL, cgroup_manager,
					slist[i], "/", me) != 0) {
			NihError *nerr;
			nerr = nih_error_get();
			ERROR("call to cgmanager_move_pid_abs_sync(%s) failed: %s",
					slist[i], nerr->message);
			nih_free(nerr);
			ret = false;
			break;
		}
	}

	return ret;
}
