static int pmcraid_reset_reload(
	struct pmcraid_instance *pinstance,
	u8 shutdown_type,
	u8 target_state
)
{
	struct pmcraid_cmd *reset_cmd = NULL;
	unsigned long lock_flags;
	int reset = 1;

	spin_lock_irqsave(pinstance->host->host_lock, lock_flags);

	if (pinstance->ioa_reset_in_progress) {
		pmcraid_info("reset_reload: reset is already in progress\n");

		spin_unlock_irqrestore(pinstance->host->host_lock, lock_flags);

		wait_event(pinstance->reset_wait_q,
			   !pinstance->ioa_reset_in_progress);

		spin_lock_irqsave(pinstance->host->host_lock, lock_flags);

		if (pinstance->ioa_state == IOA_STATE_DEAD) {
			spin_unlock_irqrestore(pinstance->host->host_lock,
					       lock_flags);
			pmcraid_info("reset_reload: IOA is dead\n");
			return reset;
		} else if (pinstance->ioa_state == target_state) {
			reset = 0;
		}
	}

	if (reset) {
		pmcraid_info("reset_reload: proceeding with reset\n");
		scsi_block_requests(pinstance->host);
		reset_cmd = pmcraid_get_free_cmd(pinstance);

		if (reset_cmd == NULL) {
			pmcraid_err("no free cmnd for reset_reload\n");
			spin_unlock_irqrestore(pinstance->host->host_lock,
					       lock_flags);
			return reset;
		}

		if (shutdown_type == SHUTDOWN_NORMAL)
			pinstance->ioa_bringdown = 1;

		pinstance->ioa_shutdown_type = shutdown_type;
		pinstance->reset_cmd = reset_cmd;
		pinstance->force_ioa_reset = reset;
		pmcraid_info("reset_reload: initiating reset\n");
		pmcraid_ioa_reset(reset_cmd);
		spin_unlock_irqrestore(pinstance->host->host_lock, lock_flags);
		pmcraid_info("reset_reload: waiting for reset to complete\n");
		wait_event(pinstance->reset_wait_q,
			   !pinstance->ioa_reset_in_progress);

		pmcraid_info("reset_reload: reset is complete !!\n");
		scsi_unblock_requests(pinstance->host);
		if (pinstance->ioa_state == target_state)
			reset = 0;
	}

	return reset;
}
