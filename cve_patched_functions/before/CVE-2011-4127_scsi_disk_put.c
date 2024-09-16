static void scsi_disk_put(struct scsi_disk *sdkp)
{
	struct scsi_device *sdev = sdkp->device;

	mutex_lock(&sd_ref_mutex);
	put_device(&sdkp->dev);
	scsi_device_put(sdev);
	mutex_unlock(&sd_ref_mutex);
}
