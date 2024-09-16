static int chown_cgroup_wrapper(void *data)
{
	struct chown_data *arg = data;
	char **slist = subsystems;
	int i, ret = -1;
	uid_t destuid;

	if (setresgid(0,0,0) < 0)
		SYSERROR("Failed to setgid to 0");
	if (setresuid(0,0,0) < 0)
		SYSERROR("Failed to setuid to 0");
	if (setgroups(0, NULL) < 0)
		SYSERROR("Failed to clear groups");
	cgm_dbus_disconnect();
	if (!cgm_dbus_connect()) {
		ERROR("Error connecting to cgroup manager");
		return -1;
	}
	destuid = get_ns_uid(arg->origuid);

	if (cgm_supports_multiple_controllers)
		slist = subsystems_inone;

	for (i = 0; slist[i]; i++) {
		if (do_chown_cgroup(slist[i], arg->cgroup_path, destuid) < 0) {
			ERROR("Failed to chown %s:%s to container root",
				slist[i], arg->cgroup_path);
			goto fail;
		}
	}
	ret = 0;
fail:
	cgm_dbus_disconnect();
	return ret;
}
