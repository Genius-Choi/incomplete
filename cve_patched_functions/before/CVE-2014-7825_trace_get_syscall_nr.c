trace_get_syscall_nr(struct task_struct *task, struct pt_regs *regs)
{
	return syscall_get_nr(task, regs);
}
