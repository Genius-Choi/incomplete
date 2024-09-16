void rpc_destroy_wait_queue(struct rpc_wait_queue *queue)
{
	del_timer_sync(&queue->timer_list.timer);
}
