static int try_to_reset_cmd_device(struct scsi_cmnd *cmd)
{
	int res;
	struct Scsi_Host *shost = cmd->device->host;

	if (!shost->hostt->eh_device_reset_handler)
		goto try_target_reset;

	res = shost->hostt->eh_device_reset_handler(cmd);
	if (res == SUCCESS)
		return res;

try_target_reset:
	if (shost->hostt->eh_target_reset_handler)
		return shost->hostt->eh_target_reset_handler(cmd);

	return FAILED;
}
