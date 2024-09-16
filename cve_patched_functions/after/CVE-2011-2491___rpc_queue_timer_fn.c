static void __rpc_queue_timer_fn(unsigned long ptr)
{
	struct rpc_wait_queue *queue = (struct rpc_wait_queue *)ptr;
	struct rpc_task *task, *n;
	unsigned long expires, now, timeo;

	spin_lock(&queue->lock);
	expires = now = jiffies;
	list_for_each_entry_safe(task, n, &queue->timer_list.list, u.tk_wait.timer_list) {
		timeo = task->u.tk_wait.expires;
		if (time_after_eq(now, timeo)) {
			dprintk("RPC: %5u timeout\n", task->tk_pid);
			task->tk_status = -ETIMEDOUT;
			rpc_wake_up_task_queue_locked(queue, task);
			continue;
		}
		if (expires == now || time_after(expires, timeo))
			expires = timeo;
	}
	if (!list_empty(&queue->timer_list.list))
		rpc_set_queue_timer(queue, expires);
	spin_unlock(&queue->lock);
}
