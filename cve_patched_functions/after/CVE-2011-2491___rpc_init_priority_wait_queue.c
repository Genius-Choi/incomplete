static void __rpc_init_priority_wait_queue(struct rpc_wait_queue *queue, const char *qname, unsigned char nr_queues)
{
	int i;

	spin_lock_init(&queue->lock);
	for (i = 0; i < ARRAY_SIZE(queue->tasks); i++)
		INIT_LIST_HEAD(&queue->tasks[i]);
	queue->maxpriority = nr_queues - 1;
	rpc_reset_waitqueue_priority(queue);
	queue->qlen = 0;
	setup_timer(&queue->timer_list.timer, __rpc_queue_timer_fn, (unsigned long)queue);
	INIT_LIST_HEAD(&queue->timer_list.list);
#ifdef RPC_DEBUG
	queue->name = qname;
#endif
}
