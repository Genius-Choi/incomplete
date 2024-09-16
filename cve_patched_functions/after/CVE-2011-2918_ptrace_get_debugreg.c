static unsigned long ptrace_get_debugreg(struct task_struct *tsk, int n)
{
	struct thread_struct *thread = &(tsk->thread);
	unsigned long val = 0;

	if (n < HBP_NUM) {
		struct perf_event *bp;

		if (ptrace_get_breakpoints(tsk) < 0)
			return -ESRCH;

		bp = thread->ptrace_bps[n];
		if (!bp)
			val = 0;
		else
			val = bp->hw.info.address;

		ptrace_put_breakpoints(tsk);
	} else if (n == 6) {
		val = thread->debugreg6;
	 } else if (n == 7) {
		val = thread->ptrace_dr7;
	}
	return val;
}
