static bool cgm_attach(const char *name, const char *lxcpath, pid_t pid)
{
	bool pass = true;
	char *cgroup = NULL;
	char **slist = subsystems;
	int i;

	if (!cgm_dbus_connect()) {
		ERROR("Error connecting to cgroup manager");
		return false;
	}

	for (i = 0; slist[i]; i++) {
		cgroup = try_get_abs_cgroup(name, lxcpath, slist[i]);
		if (!cgroup) {
			ERROR("Failed to get cgroup for controller %s", slist[i]);
			cgm_dbus_disconnect();
			return false;
		}

		if (!lxc_cgmanager_enter(pid, slist[i], cgroup, abs_cgroup_supported())) {
			pass = false;
			break;
		}

	}
	cgm_dbus_disconnect();
	if (!pass)
		ERROR("Failed to enter group %s", cgroup);

	free_abs_cgroup(cgroup);
	return pass;
}
