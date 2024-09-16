rpc_restart_call(struct rpc_task *task)
{
	if (RPC_ASSASSINATED(task))
		return 0;
	task->tk_action = call_start;
	return 1;
}
