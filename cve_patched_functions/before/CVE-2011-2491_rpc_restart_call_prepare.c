rpc_restart_call_prepare(struct rpc_task *task)
{
	if (RPC_ASSASSINATED(task))
		return 0;
	task->tk_action = rpc_prepare_task;
	return 1;
}
