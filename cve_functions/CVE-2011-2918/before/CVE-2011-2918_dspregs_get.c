static int dspregs_get(struct task_struct *target,
		       const struct user_regset *regset,
		       unsigned int pos, unsigned int count,
		       void *kbuf, void __user *ubuf)
{
	const struct pt_dspregs *regs =
		(struct pt_dspregs *)&target->thread.dsp_status.dsp_regs;
	int ret;

	ret = user_regset_copyout(&pos, &count, &kbuf, &ubuf, regs,
				  0, sizeof(struct pt_dspregs));
	if (!ret)
		ret = user_regset_copyout_zero(&pos, &count, &kbuf, &ubuf,
					       sizeof(struct pt_dspregs), -1);

	return ret;
}
