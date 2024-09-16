sd_show_app_tag_own(struct device *dev, struct device_attribute *attr,
		    char *buf)
{
	struct scsi_disk *sdkp = to_scsi_disk(dev);

	return snprintf(buf, 20, "%u\n", sdkp->ATO);
}
