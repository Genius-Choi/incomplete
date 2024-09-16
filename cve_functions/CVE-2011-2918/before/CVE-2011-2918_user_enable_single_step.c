void user_enable_single_step(struct task_struct *child)
{
	unsigned long pc = get_stack_long(child, offsetof(struct pt_regs, pc));

	set_tsk_thread_flag(child, TIF_SINGLESTEP);

	if (ptrace_get_breakpoints(child) < 0)
		return;

	set_single_step(child, pc);
	ptrace_put_breakpoints(child);
}
