static int ebb_set(struct task_struct *target,
		      const struct user_regset *regset,
		      unsigned int pos, unsigned int count,
		      const void *kbuf, const void __user *ubuf)
{
	int ret = 0;

	/* Build tests */
	BUILD_BUG_ON(TSO(ebbrr) + sizeof(unsigned long) != TSO(ebbhr));
	BUILD_BUG_ON(TSO(ebbhr) + sizeof(unsigned long) != TSO(bescr));

	if (!cpu_has_feature(CPU_FTR_ARCH_207S))
		return -ENODEV;

	if (target->thread.used_ebb)
		return -ENODATA;

	ret = user_regset_copyin(&pos, &count, &kbuf, &ubuf,
			&target->thread.ebbrr, 0, sizeof(unsigned long));

	if (!ret)
		ret = user_regset_copyin(&pos, &count, &kbuf, &ubuf,
			&target->thread.ebbhr, sizeof(unsigned long),
			2 * sizeof(unsigned long));

	if (!ret)
		ret = user_regset_copyin(&pos, &count, &kbuf, &ubuf,
			&target->thread.bescr,
			2 * sizeof(unsigned long), 3 * sizeof(unsigned long));

	return ret;
}
