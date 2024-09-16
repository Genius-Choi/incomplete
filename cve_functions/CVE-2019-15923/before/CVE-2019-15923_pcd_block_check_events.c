static unsigned int pcd_block_check_events(struct gendisk *disk,
					   unsigned int clearing)
{
	struct pcd_unit *cd = disk->private_data;
	return cdrom_check_events(&cd->info, clearing);
}
