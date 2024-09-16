void perf_event_fork(struct task_struct *task)
{
	perf_event_task(task, NULL, 1);
}
