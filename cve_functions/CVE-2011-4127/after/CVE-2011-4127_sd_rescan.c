static void sd_rescan(struct device *dev)
{
	struct scsi_disk *sdkp = scsi_disk_get_from_dev(dev);

	if (sdkp) {
		revalidate_disk(sdkp->disk);
		scsi_disk_put(sdkp);
	}
}
