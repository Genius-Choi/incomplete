unsigned int cdrom_check_events(struct cdrom_device_info *cdi,
				unsigned int clearing)
{
	unsigned int events;

	cdrom_update_events(cdi, clearing);
	events = cdi->vfs_events;
	cdi->vfs_events = 0;
	return events;
}
