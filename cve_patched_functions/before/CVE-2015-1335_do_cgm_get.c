static void do_cgm_get(const char *name, const char *lxcpath, const char *filename, int outp, bool sendvalue)
{
	char *controller, *key, *cgroup = NULL, *cglast;
	int len = -1;
	int ret;
	nih_local char *result = NULL;

	controller = alloca(strlen(filename)+1);
	strcpy(controller, filename);
	key = strchr(controller, '.');
	if (!key) {
		ret = write(outp, &len, sizeof(len));
		if (ret != sizeof(len))
			WARN("Failed to warn cgm_get of error; parent may hang");
		exit(1);
	}
	*key = '\0';

	if (!cgm_dbus_connect()) {
		ERROR("Error connecting to cgroup manager");
		ret = write(outp, &len, sizeof(len));
		if (ret != sizeof(len))
			WARN("Failed to warn cgm_get of error; parent may hang");
		exit(1);
	}
	cgroup = try_get_abs_cgroup(name, lxcpath, controller);
	if (!cgroup) {
		cgm_dbus_disconnect();
		ret = write(outp, &len, sizeof(len));
		if (ret != sizeof(len))
			WARN("Failed to warn cgm_get of error; parent may hang");
		exit(1);
	}
	cglast = strrchr(cgroup, '/');
	if (!cglast) {
		cgm_dbus_disconnect();
		free_abs_cgroup(cgroup);
		ret = write(outp, &len, sizeof(len));
		if (ret != sizeof(len))
			WARN("Failed to warn cgm_get of error; parent may hang");
		exit(1);
	}
	*cglast = '\0';
	if (!lxc_cgmanager_enter(getpid(), controller, cgroup, abs_cgroup_supported())) {
		ERROR("Failed to enter container cgroup %s:%s", controller, cgroup);
		ret = write(outp, &len, sizeof(len));
		if (ret != sizeof(len))
			WARN("Failed to warn cgm_get of error; parent may hang");
		cgm_dbus_disconnect();
		free_abs_cgroup(cgroup);
		exit(1);
	}
	if (cgmanager_get_value_sync(NULL, cgroup_manager, controller, cglast+1, filename, &result) != 0) {
		NihError *nerr;
		nerr = nih_error_get();
		nih_free(nerr);
		free_abs_cgroup(cgroup);
		cgm_dbus_disconnect();
		ret = write(outp, &len, sizeof(len));
		if (ret != sizeof(len))
			WARN("Failed to warn cgm_get of error; parent may hang");
		exit(1);
	}
	free_abs_cgroup(cgroup);
	cgm_dbus_disconnect();
	len = strlen(result);
	ret = write(outp, &len, sizeof(len));
	if (ret != sizeof(len)) {
		WARN("Failed to send length to parent");
		exit(1);
	}
	if (!len || !sendvalue) {
		exit(0);
	}
	ret = write(outp, result, len);
	if (ret < 0)
		exit(1);
	exit(0);
}
