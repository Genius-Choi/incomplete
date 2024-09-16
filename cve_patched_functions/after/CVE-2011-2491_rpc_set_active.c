static void rpc_set_active(struct rpc_task *task)
{
	rpc_task_set_debuginfo(task);
	set_bit(RPC_TASK_ACTIVE, &task->tk_runstate);
}
