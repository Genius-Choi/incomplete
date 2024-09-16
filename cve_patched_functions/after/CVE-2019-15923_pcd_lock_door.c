static int pcd_lock_door(struct cdrom_device_info *cdi, int lock)
{
	char un_cmd[12] = { 0x1e, 0, 0, 0, lock, 0, 0, 0, 0, 0, 0, 0 };

	return pcd_atapi(cdi->handle, un_cmd, 0, pcd_scratch,
			 lock ? "lock door" : "unlock door");
}
