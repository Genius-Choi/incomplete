static void rpc_free_task(struct rpc_task *task)
{
	const struct rpc_call_ops *tk_ops = task->tk_ops;
	void *calldata = task->tk_calldata;

	if (task->tk_flags & RPC_TASK_DYNAMIC) {
		dprintk("RPC: %5u freeing task\n", task->tk_pid);
		mempool_free(task, rpc_task_mempool);
	}
	rpc_release_calldata(tk_ops, calldata);
}
