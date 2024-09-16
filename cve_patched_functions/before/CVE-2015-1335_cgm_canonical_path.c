static const char *cgm_canonical_path(void *hdata)
{
	struct cgm_data *d = hdata;

	if (!d || !d->cgroup_path)
		return NULL;
	return d->cgroup_path;
}
