static inline bool cgfs_create(void *hdata)
{
	struct cgfs_data *d = hdata;
	struct cgroup_process_info *i;
	struct cgroup_meta_data *md;

	if (!d)
		return false;
	md = d->meta;
	i = lxc_cgroupfs_create(d->name, d->cgroup_pattern, md, NULL);
	if (!i)
		return false;
	d->info = i;
	return true;
}
