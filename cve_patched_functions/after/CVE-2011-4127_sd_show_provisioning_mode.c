sd_show_provisioning_mode(struct device *dev, struct device_attribute *attr,
			  char *buf)
{
	struct scsi_disk *sdkp = to_scsi_disk(dev);

	return snprintf(buf, 20, "%s\n", lbp_mode[sdkp->provisioning_mode]);
}
