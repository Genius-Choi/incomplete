static int pcd_block_ioctl(struct block_device *bdev, fmode_t mode,
				unsigned cmd, unsigned long arg)
{
	struct pcd_unit *cd = bdev->bd_disk->private_data;
	int ret;

	mutex_lock(&pcd_mutex);
	ret = cdrom_ioctl(&cd->info, bdev, mode, cmd, arg);
	mutex_unlock(&pcd_mutex);

	return ret;
}
