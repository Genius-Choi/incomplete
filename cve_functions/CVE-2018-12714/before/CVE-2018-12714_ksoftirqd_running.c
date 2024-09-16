static bool ksoftirqd_running(void)
{
	struct task_struct *tsk = __this_cpu_read(ksoftirqd);

	return tsk && (tsk->state == TASK_RUNNING);
}
