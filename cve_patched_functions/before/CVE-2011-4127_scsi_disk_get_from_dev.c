static struct scsi_disk *scsi_disk_get_from_dev(struct device *dev)
{
	struct scsi_disk *sdkp;

	mutex_lock(&sd_ref_mutex);
	sdkp = dev_get_drvdata(dev);
	if (sdkp)
		sdkp = __scsi_disk_get(sdkp->disk);
	mutex_unlock(&sd_ref_mutex);
	return sdkp;
}
