static void sas_ata_internal_abort(struct sas_task *task)
{
	struct sas_internal *si = dev_to_sas_internal(task->dev);
	unsigned long flags;
	int res;

	spin_lock_irqsave(&task->task_state_lock, flags);
	if (task->task_state_flags & SAS_TASK_STATE_ABORTED ||
	    task->task_state_flags & SAS_TASK_STATE_DONE) {
		spin_unlock_irqrestore(&task->task_state_lock, flags);
		SAS_DPRINTK("%s: Task %p already finished.\n", __func__,
			    task);
		goto out;
	}
	task->task_state_flags |= SAS_TASK_STATE_ABORTED;
	spin_unlock_irqrestore(&task->task_state_lock, flags);

	res = si->dft->lldd_abort_task(task);

	spin_lock_irqsave(&task->task_state_lock, flags);
	if (task->task_state_flags & SAS_TASK_STATE_DONE ||
	    res == TMF_RESP_FUNC_COMPLETE) {
		spin_unlock_irqrestore(&task->task_state_lock, flags);
		goto out;
	}

	/* XXX we are not prepared to deal with ->lldd_abort_task()
	 * failures.  TODO: lldds need to unconditionally forget about
	 * aborted ata tasks, otherwise we (likely) leak the sas task
	 * here
	 */
	SAS_DPRINTK("%s: Task %p leaked.\n", __func__, task);

	if (!(task->task_state_flags & SAS_TASK_STATE_DONE))
		task->task_state_flags &= ~SAS_TASK_STATE_ABORTED;
	spin_unlock_irqrestore(&task->task_state_lock, flags);

	return;
 out:
	sas_free_task(task);
}
