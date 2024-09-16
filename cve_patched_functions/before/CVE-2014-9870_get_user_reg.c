static inline long get_user_reg(struct task_struct *task, int offset)
{
	return task_pt_regs(task)->uregs[offset];
}
