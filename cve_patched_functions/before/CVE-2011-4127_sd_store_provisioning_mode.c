sd_store_provisioning_mode(struct device *dev, struct device_attribute *attr,
			   const char *buf, size_t count)
{
	struct scsi_disk *sdkp = to_scsi_disk(dev);
	struct scsi_device *sdp = sdkp->device;

	if (!capable(CAP_SYS_ADMIN))
		return -EACCES;

	if (sdp->type != TYPE_DISK)
		return -EINVAL;

	if (!strncmp(buf, lbp_mode[SD_LBP_UNMAP], 20))
		sd_config_discard(sdkp, SD_LBP_UNMAP);
	else if (!strncmp(buf, lbp_mode[SD_LBP_WS16], 20))
		sd_config_discard(sdkp, SD_LBP_WS16);
	else if (!strncmp(buf, lbp_mode[SD_LBP_WS10], 20))
		sd_config_discard(sdkp, SD_LBP_WS10);
	else if (!strncmp(buf, lbp_mode[SD_LBP_ZERO], 20))
		sd_config_discard(sdkp, SD_LBP_ZERO);
	else if (!strncmp(buf, lbp_mode[SD_LBP_DISABLE], 20))
		sd_config_discard(sdkp, SD_LBP_DISABLE);
	else
		return -EINVAL;

	return count;
}
