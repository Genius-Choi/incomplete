static int sd_try_rc16_first(struct scsi_device *sdp)
{
	if (sdp->host->max_cmd_len < 16)
		return 0;
	if (sdp->scsi_level > SCSI_SPC_2)
		return 1;
	if (scsi_device_protection(sdp))
		return 1;
	return 0;
}
