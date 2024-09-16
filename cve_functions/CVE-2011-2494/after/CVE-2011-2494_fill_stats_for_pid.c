static int fill_stats_for_pid(pid_t pid, struct taskstats *stats)
{
	struct task_struct *tsk;

	rcu_read_lock();
	tsk = find_task_by_vpid(pid);
	if (tsk)
		get_task_struct(tsk);
	rcu_read_unlock();
	if (!tsk)
		return -ESRCH;
	fill_stats(tsk, stats);
	put_task_struct(tsk);
	return 0;
}
