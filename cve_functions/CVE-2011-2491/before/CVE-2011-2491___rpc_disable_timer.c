__rpc_disable_timer(struct rpc_wait_queue *queue, struct rpc_task *task)
{
	if (task->tk_timeout == 0)
		return;
	dprintk("RPC: %5u disabling timer\n", task->tk_pid);
	task->tk_timeout = 0;
	list_del(&task->u.tk_wait.timer_list);
	if (list_empty(&queue->timer_list.list))
		del_timer(&queue->timer_list.timer);
}
