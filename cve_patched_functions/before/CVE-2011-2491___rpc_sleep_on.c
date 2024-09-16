static void __rpc_sleep_on(struct rpc_wait_queue *q, struct rpc_task *task,
			rpc_action action)
{
	dprintk("RPC: %5u sleep_on(queue \"%s\" time %lu)\n",
			task->tk_pid, rpc_qname(q), jiffies);

	__rpc_add_wait_queue(q, task);

	BUG_ON(task->tk_callback != NULL);
	task->tk_callback = action;
	__rpc_add_timer(q, task);
}
