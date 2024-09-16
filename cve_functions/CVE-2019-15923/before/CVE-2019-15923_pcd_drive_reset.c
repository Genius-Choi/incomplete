static int pcd_drive_reset(struct cdrom_device_info *cdi)
{
	return pcd_reset(cdi->handle);
}
