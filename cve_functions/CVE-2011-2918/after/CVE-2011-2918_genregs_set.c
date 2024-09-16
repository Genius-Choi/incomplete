static int genregs_set(struct task_struct *target,
		       const struct user_regset *regset,
		       unsigned int pos, unsigned int count,
		       const void *kbuf, const void __user *ubuf)
{
	struct pt_regs *regs = task_pt_regs(target);
	int ret;

	ret = user_regset_copyin(&pos, &count, &kbuf, &ubuf,
				 regs->regs,
				 0, 16 * sizeof(unsigned long));
	if (!ret && count > 0)
		ret = user_regset_copyin(&pos, &count, &kbuf, &ubuf,
					 &regs->pc,
					 offsetof(struct pt_regs, pc),
					 sizeof(struct pt_regs));
	if (!ret)
		ret = user_regset_copyin_ignore(&pos, &count, &kbuf, &ubuf,
						sizeof(struct pt_regs), -1);

	return ret;
}
