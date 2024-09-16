asmlinkage void do_syscall_trace_leave(struct pt_regs *regs)
{
	int step;

	if (unlikely(current->audit_context))
		audit_syscall_exit(AUDITSC_RESULT(regs->regs[0]),
				   regs->regs[0]);

	if (unlikely(test_thread_flag(TIF_SYSCALL_TRACEPOINT)))
		trace_sys_exit(regs, regs->regs[0]);

	step = test_thread_flag(TIF_SINGLESTEP);
	if (step || test_thread_flag(TIF_SYSCALL_TRACE))
		tracehook_report_syscall_exit(regs, step);
}
