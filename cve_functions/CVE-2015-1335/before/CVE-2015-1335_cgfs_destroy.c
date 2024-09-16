static void cgfs_destroy(void *hdata)
{
	struct cgfs_data *d = hdata;

	if (!d)
		return;
	free(d->name);
	lxc_cgroup_process_info_free_and_remove(d->info);
	lxc_cgroup_put_meta(d->meta);
	free(d);
}
