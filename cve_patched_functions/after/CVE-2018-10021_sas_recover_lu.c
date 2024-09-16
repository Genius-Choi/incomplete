static int sas_recover_lu(struct domain_device *dev, struct scsi_cmnd *cmd)
{
	int res = TMF_RESP_FUNC_FAILED;
	struct scsi_lun lun;
	struct sas_internal *i =
		to_sas_internal(dev->port->ha->core.shost->transportt);

	int_to_scsilun(cmd->device->lun, &lun);

	SAS_DPRINTK("eh: device %llx LUN %llx has the task\n",
		    SAS_ADDR(dev->sas_addr),
		    cmd->device->lun);

	if (i->dft->lldd_abort_task_set)
		res = i->dft->lldd_abort_task_set(dev, lun.scsi_lun);

	if (res == TMF_RESP_FUNC_FAILED) {
		if (i->dft->lldd_clear_task_set)
			res = i->dft->lldd_clear_task_set(dev, lun.scsi_lun);
	}

	if (res == TMF_RESP_FUNC_FAILED) {
		if (i->dft->lldd_lu_reset)
			res = i->dft->lldd_lu_reset(dev, lun.scsi_lun);
	}

	return res;
}
