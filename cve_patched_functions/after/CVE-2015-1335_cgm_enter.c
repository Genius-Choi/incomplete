static inline bool cgm_enter(void *hdata, pid_t pid)
{
	struct cgm_data *d = hdata;
	char **slist = subsystems;
	bool ret = false;
	int i;

	if (!d || !d->cgroup_path)
		return false;

	if (!cgm_dbus_connect()) {
		ERROR("Error connecting to cgroup manager");
		return false;
	}

	if (cgm_all_controllers_same)
		slist = subsystems_inone;

	for (i = 0; slist[i]; i++) {
		if (!lxc_cgmanager_enter(pid, slist[i], d->cgroup_path, false))
			goto out;
	}
	ret = true;
out:
	cgm_dbus_disconnect();
	return ret;
}
