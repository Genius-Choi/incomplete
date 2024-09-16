static unsigned int pcd_check_events(struct cdrom_device_info *cdi,
				     unsigned int clearing, int slot_nr)
{
	struct pcd_unit *cd = cdi->handle;
	int res = cd->changed;
	if (res)
		cd->changed = 0;
	return res ? DISK_EVENT_MEDIA_CHANGE : 0;
}
