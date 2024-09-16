void sched_ttwu_pending(void)
{
	struct rq *rq = this_rq();
	struct llist_node *llist = llist_del_all(&rq->wake_list);
	struct pin_cookie cookie;
	struct task_struct *p;
	unsigned long flags;

	if (!llist)
		return;

	raw_spin_lock_irqsave(&rq->lock, flags);
	cookie = lockdep_pin_lock(&rq->lock);

	while (llist) {
		int wake_flags = 0;

		p = llist_entry(llist, struct task_struct, wake_entry);
		llist = llist_next(llist);

		if (p->sched_remote_wakeup)
			wake_flags = WF_MIGRATED;

		ttwu_do_activate(rq, p, wake_flags, cookie);
	}

	lockdep_unpin_lock(&rq->lock, cookie);
	raw_spin_unlock_irqrestore(&rq->lock, flags);
}
