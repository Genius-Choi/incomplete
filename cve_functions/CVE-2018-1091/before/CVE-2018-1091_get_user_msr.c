static unsigned long get_user_msr(struct task_struct *task)
{
	return task->thread.regs->msr | task->thread.fpexc_mode;
}
