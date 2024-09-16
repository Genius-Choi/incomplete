__rpc_add_timer(struct rpc_wait_queue *queue, struct rpc_task *task)
{
	if (!task->tk_timeout)
		return;

	dprintk("RPC: %5u setting alarm for %lu ms\n",
			task->tk_pid, task->tk_timeout * 1000 / HZ);

	task->u.tk_wait.expires = jiffies + task->tk_timeout;
	if (list_empty(&queue->timer_list.list) || time_before(task->u.tk_wait.expires, queue->timer_list.expires))
		rpc_set_queue_timer(queue, task->u.tk_wait.expires);
	list_add(&task->u.tk_wait.timer_list, &queue->timer_list.list);
}
