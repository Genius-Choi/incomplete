static void delayed_put_task_struct(struct rcu_head *rhp)
{
	struct task_struct *tsk = container_of(rhp, struct task_struct, rcu);

	trace_sched_process_free(tsk);
	put_task_struct(tsk);
}
