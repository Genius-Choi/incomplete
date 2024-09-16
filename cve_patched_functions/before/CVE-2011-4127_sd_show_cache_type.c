sd_show_cache_type(struct device *dev, struct device_attribute *attr,
		   char *buf)
{
	struct scsi_disk *sdkp = to_scsi_disk(dev);
	int ct = sdkp->RCD + 2*sdkp->WCE;

	return snprintf(buf, 40, "%s\n", sd_cache_types[ct]);
}
