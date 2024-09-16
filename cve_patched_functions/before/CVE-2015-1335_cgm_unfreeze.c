static bool cgm_unfreeze(void *hdata)
{
	struct cgm_data *d = hdata;
	bool ret = true;

	if (!d || !d->cgroup_path)
		return false;

	if (!cgm_dbus_connect()) {
		ERROR("Error connecting to cgroup manager");
		return false;
	}
	if (cgmanager_set_value_sync(NULL, cgroup_manager, "freezer", d->cgroup_path,
			"freezer.state", "THAWED") != 0) {
		NihError *nerr;
		nerr = nih_error_get();
		ERROR("call to cgmanager_set_value_sync failed: %s", nerr->message);
		nih_free(nerr);
		ERROR("Error unfreezing %s", d->cgroup_path);
		ret = false;
	}
	cgm_dbus_disconnect();
	return ret;
}
