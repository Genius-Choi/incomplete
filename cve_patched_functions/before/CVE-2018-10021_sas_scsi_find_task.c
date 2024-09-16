static enum task_disposition sas_scsi_find_task(struct sas_task *task)
{
	unsigned long flags;
	int i, res;
	struct sas_internal *si =
		to_sas_internal(task->dev->port->ha->core.shost->transportt);

	for (i = 0; i < 5; i++) {
		SAS_DPRINTK("%s: aborting task 0x%p\n", __func__, task);
		res = si->dft->lldd_abort_task(task);

		spin_lock_irqsave(&task->task_state_lock, flags);
		if (task->task_state_flags & SAS_TASK_STATE_DONE) {
			spin_unlock_irqrestore(&task->task_state_lock, flags);
			SAS_DPRINTK("%s: task 0x%p is done\n", __func__,
				    task);
			return TASK_IS_DONE;
		}
		spin_unlock_irqrestore(&task->task_state_lock, flags);

		if (res == TMF_RESP_FUNC_COMPLETE) {
			SAS_DPRINTK("%s: task 0x%p is aborted\n",
				    __func__, task);
			return TASK_IS_ABORTED;
		} else if (si->dft->lldd_query_task) {
			SAS_DPRINTK("%s: querying task 0x%p\n",
				    __func__, task);
			res = si->dft->lldd_query_task(task);
			switch (res) {
			case TMF_RESP_FUNC_SUCC:
				SAS_DPRINTK("%s: task 0x%p at LU\n",
					    __func__, task);
				return TASK_IS_AT_LU;
			case TMF_RESP_FUNC_COMPLETE:
				SAS_DPRINTK("%s: task 0x%p not at LU\n",
					    __func__, task);
				return TASK_IS_NOT_AT_LU;
			case TMF_RESP_FUNC_FAILED:
                                SAS_DPRINTK("%s: task 0x%p failed to abort\n",
                                                __func__, task);
                                return TASK_ABORT_FAILED;
                        }

		}
	}
	return res;
}
