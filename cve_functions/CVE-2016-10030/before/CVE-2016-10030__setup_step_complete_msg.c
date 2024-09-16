static void _setup_step_complete_msg(slurm_msg_t *msg, void *data)
{
	slurm_msg_t_init(msg);
	msg->msg_type = REQUEST_STEP_COMPLETE;
	msg->data = data;
}
