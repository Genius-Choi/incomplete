static int s390_tdb_get(struct task_struct *target,
			const struct user_regset *regset,
			unsigned int pos, unsigned int count,
			void *kbuf, void __user *ubuf)
{
	struct pt_regs *regs = task_pt_regs(target);
	unsigned char *data;

	if (!(regs->int_code & 0x200))
		return -ENODATA;
	data = target->thread.trap_tdb;
	return user_regset_copyout(&pos, &count, &kbuf, &ubuf, data, 0, 256);
}
