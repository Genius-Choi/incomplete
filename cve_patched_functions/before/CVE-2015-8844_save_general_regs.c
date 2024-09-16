static inline int save_general_regs(struct pt_regs *regs,
		struct mcontext __user *frame)
{
	WARN_ON(!FULL_REGS(regs));
	return __copy_to_user(&frame->mc_gregs, regs, GP_REGS_SIZE);
}
