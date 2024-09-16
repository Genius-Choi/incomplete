static void pcd_block_release(struct gendisk *disk, fmode_t mode)
{
	struct pcd_unit *cd = disk->private_data;
	mutex_lock(&pcd_mutex);
	cdrom_release(&cd->info, mode);
	mutex_unlock(&pcd_mutex);
}
