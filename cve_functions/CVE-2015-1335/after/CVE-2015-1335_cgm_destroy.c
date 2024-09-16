static void cgm_destroy(void *hdata)
{
	struct cgm_data *d = hdata;
	char **slist = subsystems;
	int i;

	if (!d || !d->cgroup_path)
		return;
	if (!cgm_dbus_connect()) {
		ERROR("Error connecting to cgroup manager");
		return;
	}

	if (cgm_supports_multiple_controllers)
		slist = subsystems_inone;
	for (i = 0; slist[i]; i++)
		cgm_remove_cgroup(slist[i], d->cgroup_path);

	free(d->name);
	free(d->cgroup_path);
	free(d);
	cgm_dbus_disconnect();
}
