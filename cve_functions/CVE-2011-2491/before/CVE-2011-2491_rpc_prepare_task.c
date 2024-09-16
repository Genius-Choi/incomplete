void rpc_prepare_task(struct rpc_task *task)
{
	task->tk_ops->rpc_call_prepare(task, task->tk_calldata);
}
