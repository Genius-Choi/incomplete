void perf_event_delayed_put(struct task_struct *task)
{
	int ctxn;

	for_each_task_context_nr(ctxn)
		WARN_ON_ONCE(task->perf_event_ctxp[ctxn]);
}
