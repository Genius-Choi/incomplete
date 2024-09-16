void rpc_wake_up_queued_task(struct rpc_wait_queue *queue, struct rpc_task *task)
{
	spin_lock_bh(&queue->lock);
	rpc_wake_up_task_queue_locked(queue, task);
	spin_unlock_bh(&queue->lock);
}
