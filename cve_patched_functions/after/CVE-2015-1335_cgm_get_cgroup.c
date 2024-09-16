static const char *cgm_get_cgroup(void *hdata, const char *subsystem)
{
	struct cgm_data *d = hdata;

	if (!d || !d->cgroup_path)
		return NULL;
	return d->cgroup_path;
}
