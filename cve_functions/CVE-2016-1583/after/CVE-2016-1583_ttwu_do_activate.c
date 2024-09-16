ttwu_do_activate(struct rq *rq, struct task_struct *p, int wake_flags,
		 struct pin_cookie cookie)
{
	int en_flags = ENQUEUE_WAKEUP;

	lockdep_assert_held(&rq->lock);

#ifdef CONFIG_SMP
	if (p->sched_contributes_to_load)
		rq->nr_uninterruptible--;

	if (wake_flags & WF_MIGRATED)
		en_flags |= ENQUEUE_MIGRATED;
#endif

	ttwu_activate(rq, p, en_flags);
	ttwu_do_wakeup(rq, p, wake_flags, cookie);
}
