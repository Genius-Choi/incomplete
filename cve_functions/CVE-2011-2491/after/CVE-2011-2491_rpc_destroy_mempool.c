rpc_destroy_mempool(void)
{
	rpciod_stop();
	if (rpc_buffer_mempool)
		mempool_destroy(rpc_buffer_mempool);
	if (rpc_task_mempool)
		mempool_destroy(rpc_task_mempool);
	if (rpc_task_slabp)
		kmem_cache_destroy(rpc_task_slabp);
	if (rpc_buffer_slabp)
		kmem_cache_destroy(rpc_buffer_slabp);
	rpc_destroy_wait_queue(&delay_queue);
}
