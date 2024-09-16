static void rpc_wake_up_task_queue_locked(struct rpc_wait_queue *queue, struct rpc_task *task)
{
	if (RPC_IS_QUEUED(task) && task->tk_waitqueue == queue)
		__rpc_do_wake_up_task(queue, task);
}
