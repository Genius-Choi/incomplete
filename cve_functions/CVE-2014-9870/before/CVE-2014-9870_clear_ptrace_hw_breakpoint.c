void clear_ptrace_hw_breakpoint(struct task_struct *tsk)
{
	memset(tsk->thread.debug.hbp, 0, sizeof(tsk->thread.debug.hbp));
}
