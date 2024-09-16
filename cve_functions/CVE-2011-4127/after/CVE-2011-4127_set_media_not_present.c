static void set_media_not_present(struct scsi_disk *sdkp)
{
	if (sdkp->media_present)
		sdkp->device->changed = 1;

	if (sdkp->device->removable) {
		sdkp->media_present = 0;
		sdkp->capacity = 0;
	}
}
