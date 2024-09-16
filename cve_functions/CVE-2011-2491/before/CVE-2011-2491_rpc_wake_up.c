void rpc_wake_up(struct rpc_wait_queue *queue)
{
	struct rpc_task *task, *next;
	struct list_head *head;

	spin_lock_bh(&queue->lock);
	head = &queue->tasks[queue->maxpriority];
	for (;;) {
		list_for_each_entry_safe(task, next, head, u.tk_wait.list)
			rpc_wake_up_task_queue_locked(queue, task);
		if (head == &queue->tasks[0])
			break;
		head--;
	}
	spin_unlock_bh(&queue->lock);
}
