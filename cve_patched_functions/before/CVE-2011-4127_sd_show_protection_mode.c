sd_show_protection_mode(struct device *dev, struct device_attribute *attr,
			char *buf)
{
	struct scsi_disk *sdkp = to_scsi_disk(dev);
	struct scsi_device *sdp = sdkp->device;
	unsigned int dif, dix;

	dif = scsi_host_dif_capable(sdp->host, sdkp->protection_type);
	dix = scsi_host_dix_capable(sdp->host, sdkp->protection_type);

	if (!dix && scsi_host_dix_capable(sdp->host, SD_DIF_TYPE0_PROTECTION)) {
		dif = 0;
		dix = 1;
	}

	if (!dif && !dix)
		return snprintf(buf, 20, "none\n");

	return snprintf(buf, 20, "%s%u\n", dix ? "dix" : "dif", dif);
}
