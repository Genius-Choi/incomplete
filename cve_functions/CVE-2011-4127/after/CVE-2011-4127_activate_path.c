static void activate_path(struct work_struct *work)
{
	struct pgpath *pgpath =
		container_of(work, struct pgpath, activate_path.work);

	scsi_dh_activate(bdev_get_queue(pgpath->path.dev->bdev),
				pg_init_done, pgpath);
}
