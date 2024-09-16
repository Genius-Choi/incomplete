int sas_eh_target_reset_handler(struct scsi_cmnd *cmd)
{
	int res;
	struct Scsi_Host *host = cmd->device->host;
	struct domain_device *dev = cmd_to_domain_dev(cmd);
	struct sas_internal *i = to_sas_internal(host->transportt);

	if (current != host->ehandler)
		return sas_queue_reset(dev, SAS_DEV_RESET, 0, 0);

	if (!i->dft->lldd_I_T_nexus_reset)
		return FAILED;

	res = i->dft->lldd_I_T_nexus_reset(dev);
	if (res == TMF_RESP_FUNC_SUCC || res == TMF_RESP_FUNC_COMPLETE ||
	    res == -ENODEV)
		return SUCCESS;

	return FAILED;
}
