static inline void rpc_set_waitqueue_owner(struct rpc_wait_queue *queue, pid_t pid)
{
	queue->owner = pid;
	queue->nr = RPC_BATCH_COUNT;
}
