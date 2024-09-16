sd_store_manage_start_stop(struct device *dev, struct device_attribute *attr,
			   const char *buf, size_t count)
{
	struct scsi_disk *sdkp = to_scsi_disk(dev);
	struct scsi_device *sdp = sdkp->device;

	if (!capable(CAP_SYS_ADMIN))
		return -EACCES;

	sdp->manage_start_stop = simple_strtoul(buf, NULL, 10);

	return count;
}
