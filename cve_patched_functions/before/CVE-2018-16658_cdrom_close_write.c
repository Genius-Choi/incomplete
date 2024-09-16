static int cdrom_close_write(struct cdrom_device_info *cdi)
{
#if 0
	return cdrom_flush_cache(cdi);
#else
	return 0;
#endif
}
