void rpc_wake_up_status(struct rpc_wait_queue *queue, int status)
{
	struct rpc_task *task, *next;
	struct list_head *head;

	spin_lock_bh(&queue->lock);
	head = &queue->tasks[queue->maxpriority];
	for (;;) {
		list_for_each_entry_safe(task, next, head, u.tk_wait.list) {
			task->tk_status = status;
			rpc_wake_up_task_queue_locked(queue, task);
		}
		if (head == &queue->tasks[0])
			break;
		head--;
	}
	spin_unlock_bh(&queue->lock);
}
