static int sd_resume(struct device *dev)
{
	struct scsi_disk *sdkp = scsi_disk_get_from_dev(dev);
	int ret = 0;

	if (!sdkp->device->manage_start_stop)
		goto done;

	sd_printk(KERN_NOTICE, sdkp, "Starting disk\n");
	ret = sd_start_stop_device(sdkp, 1);

done:
	scsi_disk_put(sdkp);
	return ret;
}
