int sas_eh_device_reset_handler(struct scsi_cmnd *cmd)
{
	int res;
	struct scsi_lun lun;
	struct Scsi_Host *host = cmd->device->host;
	struct domain_device *dev = cmd_to_domain_dev(cmd);
	struct sas_internal *i = to_sas_internal(host->transportt);

	if (current != host->ehandler)
		return sas_queue_reset(dev, SAS_DEV_LU_RESET, cmd->device->lun, 0);

	int_to_scsilun(cmd->device->lun, &lun);

	if (!i->dft->lldd_lu_reset)
		return FAILED;

	res = i->dft->lldd_lu_reset(dev, lun.scsi_lun);
	if (res == TMF_RESP_FUNC_SUCC || res == TMF_RESP_FUNC_COMPLETE)
		return SUCCESS;

	return FAILED;
}
