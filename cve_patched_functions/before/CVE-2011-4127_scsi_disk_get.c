static struct scsi_disk *scsi_disk_get(struct gendisk *disk)
{
	struct scsi_disk *sdkp;

	mutex_lock(&sd_ref_mutex);
	sdkp = __scsi_disk_get(disk);
	mutex_unlock(&sd_ref_mutex);
	return sdkp;
}
