static void _handle_old_batch_job_launch(slurm_msg_t *msg)
{
	if (msg->msg_type != REQUEST_BATCH_JOB_LAUNCH) {
		error("_handle_batch_job_launch: "
		      "Invalid response msg_type (%u)", msg->msg_type);
		return;
	}

	/* (resp_msg.msg_type == REQUEST_BATCH_JOB_LAUNCH) */
	debug2("Processing RPC: REQUEST_BATCH_JOB_LAUNCH");
	last_slurmctld_msg = time(NULL);
	_rpc_batch_job(msg, false);
	slurm_free_job_launch_msg(msg->data);
	msg->data = NULL;

}
