static void rds_loop_conn_free(void *arg)
{
	struct rds_loop_connection *lc = arg;
	unsigned long flags;

	rdsdebug("lc %p\n", lc);
	spin_lock_irqsave(&loop_conns_lock, flags);
	list_del(&lc->loop_node);
	spin_unlock_irqrestore(&loop_conns_lock, flags);
	kfree(lc);
}
