static unsigned long get_user_ckpt_msr(struct task_struct *task)
{
	return task->thread.ckpt_regs.msr | task->thread.fpexc_mode;
}
