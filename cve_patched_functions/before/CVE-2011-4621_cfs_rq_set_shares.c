static void cfs_rq_set_shares(struct cfs_rq *cfs_rq, unsigned long shares)
{
#ifdef CONFIG_SMP
	cfs_rq->shares = shares;
#endif
}
