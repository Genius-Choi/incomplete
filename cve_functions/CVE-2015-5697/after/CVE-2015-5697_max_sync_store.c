max_sync_store(struct mddev *mddev, const char *buf, size_t len)
{
	int err;
	spin_lock(&mddev->lock);
	if (strncmp(buf, "max", 3) == 0)
		mddev->resync_max = MaxSector;
	else {
		unsigned long long max;
		int chunk;

		err = -EINVAL;
		if (kstrtoull(buf, 10, &max))
			goto out_unlock;
		if (max < mddev->resync_min)
			goto out_unlock;

		err = -EBUSY;
		if (max < mddev->resync_max &&
		    mddev->ro == 0 &&
		    test_bit(MD_RECOVERY_RUNNING, &mddev->recovery))
			goto out_unlock;

		/* Must be a multiple of chunk_size */
		chunk = mddev->chunk_sectors;
		if (chunk) {
			sector_t temp = max;

			err = -EINVAL;
			if (sector_div(temp, chunk))
				goto out_unlock;
		}
		mddev->resync_max = max;
	}
	wake_up(&mddev->recovery_wait);
	err = 0;
out_unlock:
	spin_unlock(&mddev->lock);
	return err ?: len;
}
