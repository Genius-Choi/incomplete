static int cgm_get_nrtasks(void *hdata)
{
	struct cgm_data *d = hdata;
	int32_t *pids;
	size_t pids_len;

	if (!d || !d->cgroup_path)
		return -1;

	if (!cgm_dbus_connect()) {
		ERROR("Error connecting to cgroup manager");
		return -1;
	}
	if (cgmanager_get_tasks_sync(NULL, cgroup_manager, subsystems[0],
				     d->cgroup_path, &pids, &pids_len) != 0) {
		NihError *nerr;
		nerr = nih_error_get();
		ERROR("call to cgmanager_get_tasks_sync failed: %s", nerr->message);
		nih_free(nerr);
		pids_len = -1;
		goto out;
	}
	nih_free(pids);
out:
	cgm_dbus_disconnect();
	return pids_len;
}
