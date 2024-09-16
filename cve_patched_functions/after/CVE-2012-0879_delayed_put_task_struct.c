static void delayed_put_task_struct(struct rcu_head *rhp)
{
	struct task_struct *tsk = container_of(rhp, struct task_struct, rcu);

#ifdef CONFIG_PERF_EVENTS
	WARN_ON_ONCE(tsk->perf_event_ctxp);
#endif
	trace_sched_process_free(tsk);
	put_task_struct(tsk);
}
