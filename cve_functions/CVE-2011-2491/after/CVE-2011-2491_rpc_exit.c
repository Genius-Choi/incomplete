void rpc_exit(struct rpc_task *task, int status)
{
	task->tk_status = status;
	task->tk_action = rpc_exit_task;
	if (RPC_IS_QUEUED(task))
		rpc_wake_up_queued_task(task->tk_waitqueue, task);
}
