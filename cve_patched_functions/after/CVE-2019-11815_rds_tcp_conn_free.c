static void rds_tcp_conn_free(void *arg)
{
	struct rds_tcp_connection *tc = arg;
	unsigned long flags;

	rdsdebug("freeing tc %p\n", tc);

	spin_lock_irqsave(&rds_tcp_conn_lock, flags);
	if (!tc->t_tcp_node_detached)
		list_del(&tc->t_tcp_node);
	spin_unlock_irqrestore(&rds_tcp_conn_lock, flags);

	kmem_cache_free(rds_tcp_conn_slab, tc);
}
