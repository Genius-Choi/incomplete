static int s390_fpregs_get(struct task_struct *target,
			   const struct user_regset *regset, unsigned int pos,
			   unsigned int count, void *kbuf, void __user *ubuf)
{
	if (target == current) {
		save_fp_ctl(&target->thread.fp_regs.fpc);
		save_fp_regs(target->thread.fp_regs.fprs);
	}

	return user_regset_copyout(&pos, &count, &kbuf, &ubuf,
				   &target->thread.fp_regs, 0, -1);
}
