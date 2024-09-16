void perf_event_exec(void)
{
	int ctxn;

	rcu_read_lock();
	for_each_task_context_nr(ctxn)
		perf_event_enable_on_exec(ctxn);
	rcu_read_unlock();
}
