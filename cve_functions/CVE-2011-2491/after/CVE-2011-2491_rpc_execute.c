void rpc_execute(struct rpc_task *task)
{
	rpc_set_active(task);
	rpc_make_runnable(task);
	if (!RPC_IS_ASYNC(task))
		__rpc_execute(task);
}
