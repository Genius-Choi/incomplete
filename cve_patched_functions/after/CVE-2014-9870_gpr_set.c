static int gpr_set(struct task_struct *target,
		   const struct user_regset *regset,
		   unsigned int pos, unsigned int count,
		   const void *kbuf, const void __user *ubuf)
{
	int ret;
	struct pt_regs newregs;

	ret = user_regset_copyin(&pos, &count, &kbuf, &ubuf,
				 &newregs,
				 0, sizeof(newregs));
	if (ret)
		return ret;

	if (!valid_user_regs(&newregs))
		return -EINVAL;

	*task_pt_regs(target) = newregs;
	return 0;
}
