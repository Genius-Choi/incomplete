static void rds_ib_sub_signaled(struct rds_ib_connection *ic, int nr)
{
	if ((atomic_sub_return(nr, &ic->i_signaled_sends) == 0) &&
	    waitqueue_active(&rds_ib_ring_empty_wait))
		wake_up(&rds_ib_ring_empty_wait);
	BUG_ON(atomic_read(&ic->i_signaled_sends) < 0);
}
