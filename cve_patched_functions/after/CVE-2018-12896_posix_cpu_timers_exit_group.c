void posix_cpu_timers_exit_group(struct task_struct *tsk)
{
	cleanup_timers(tsk->signal->cpu_timers);
}
