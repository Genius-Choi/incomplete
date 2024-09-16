static int set_user_trap(struct task_struct *task, unsigned long trap)
{
	task->thread.regs->trap = trap & 0xfff0;
	return 0;
}
