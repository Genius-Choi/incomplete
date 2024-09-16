sd_show_manage_start_stop(struct device *dev, struct device_attribute *attr,
			  char *buf)
{
	struct scsi_disk *sdkp = to_scsi_disk(dev);
	struct scsi_device *sdp = sdkp->device;

	return snprintf(buf, 20, "%u\n", sdp->manage_start_stop);
}
