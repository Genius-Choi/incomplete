int cdrom_media_changed(struct cdrom_device_info *cdi)
{
	/* This talks to the VFS, which doesn't like errors - just 1 or 0.  
	 * Returning "0" is always safe (media hasn't been changed). Do that 
	 * if the low-level cdrom driver dosn't support media changed. */ 
	if (cdi == NULL || cdi->ops->media_changed == NULL)
		return 0;
	if (!CDROM_CAN(CDC_MEDIA_CHANGED))
		return 0;
	return media_changed(cdi, 0);
}
