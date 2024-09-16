static bool cgm_chown(void *hdata, struct lxc_conf *conf)
{
	struct cgm_data *d = hdata;

	if (!d || !d->cgroup_path)
		return false;
	if (!cgm_dbus_connect()) {
		ERROR("Error connecting to cgroup manager");
		return false;
	}
	if (!chown_cgroup(d->cgroup_path, conf))
		WARN("Failed to chown %s to container root", d->cgroup_path);
	cgm_dbus_disconnect();
	return true;
}
