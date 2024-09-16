static void set_se_shares(struct sched_entity *se, unsigned long shares)
{
	struct cfs_rq *cfs_rq = se->cfs_rq;
	struct rq *rq = cfs_rq->rq;
	unsigned long flags;

	raw_spin_lock_irqsave(&rq->lock, flags);
	__set_se_shares(se, shares);
	raw_spin_unlock_irqrestore(&rq->lock, flags);
}
