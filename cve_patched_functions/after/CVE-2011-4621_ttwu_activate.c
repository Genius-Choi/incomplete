static inline void ttwu_activate(struct task_struct *p, struct rq *rq,
				 bool is_sync, bool is_migrate, bool is_local,
				 unsigned long en_flags)
{
	schedstat_inc(p, se.statistics.nr_wakeups);
	if (is_sync)
		schedstat_inc(p, se.statistics.nr_wakeups_sync);
	if (is_migrate)
		schedstat_inc(p, se.statistics.nr_wakeups_migrate);
	if (is_local)
		schedstat_inc(p, se.statistics.nr_wakeups_local);
	else
		schedstat_inc(p, se.statistics.nr_wakeups_remote);

	activate_task(rq, p, en_flags);
}
