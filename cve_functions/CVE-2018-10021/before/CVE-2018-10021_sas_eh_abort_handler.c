int sas_eh_abort_handler(struct scsi_cmnd *cmd)
{
	int res;
	struct sas_task *task = TO_SAS_TASK(cmd);
	struct Scsi_Host *host = cmd->device->host;
	struct sas_internal *i = to_sas_internal(host->transportt);

	if (!i->dft->lldd_abort_task)
		return FAILED;

	res = i->dft->lldd_abort_task(task);
	if (res == TMF_RESP_FUNC_SUCC || res == TMF_RESP_FUNC_COMPLETE)
		return SUCCESS;

	return FAILED;
}
