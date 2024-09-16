struct rpc_task * rpc_wake_up_next(struct rpc_wait_queue *queue)
{
	struct rpc_task	*task = NULL;

	dprintk("RPC:       wake_up_next(%p \"%s\")\n",
			queue, rpc_qname(queue));
	spin_lock_bh(&queue->lock);
	if (RPC_IS_PRIORITY(queue))
		task = __rpc_wake_up_next_priority(queue);
	else {
		task_for_first(task, &queue->tasks[0])
			rpc_wake_up_task_queue_locked(queue, task);
	}
	spin_unlock_bh(&queue->lock);

	return task;
}
