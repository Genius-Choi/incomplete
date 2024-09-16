void ptrace_put_breakpoints(struct task_struct *tsk)
{
	if (atomic_dec_and_test(&tsk->ptrace_bp_refcnt))
		flush_ptrace_hw_breakpoint(tsk);
}
