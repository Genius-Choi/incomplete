static int dspregs_active(struct task_struct *target,
			  const struct user_regset *regset)
{
	struct pt_regs *regs = task_pt_regs(target);

	return regs->sr & SR_DSP ? regset->n : 0;
}
