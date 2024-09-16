static void free_pgpaths(struct list_head *pgpaths, struct dm_target *ti)
{
	struct pgpath *pgpath, *tmp;
	struct multipath *m = ti->private;

	list_for_each_entry_safe(pgpath, tmp, pgpaths, list) {
		list_del(&pgpath->list);
		if (m->hw_handler_name)
			scsi_dh_detach(bdev_get_queue(pgpath->path.dev->bdev));
		dm_put_device(ti, pgpath->path.dev);
		free_pgpath(pgpath);
	}
}
