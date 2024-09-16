static int evr_get(struct task_struct *target, const struct user_regset *regset,
		   unsigned int pos, unsigned int count,
		   void *kbuf, void __user *ubuf)
{
	int ret;

	flush_spe_to_thread(target);

	ret = user_regset_copyout(&pos, &count, &kbuf, &ubuf,
				  &target->thread.evr,
				  0, sizeof(target->thread.evr));

	BUILD_BUG_ON(offsetof(struct thread_struct, acc) + sizeof(u64) !=
		     offsetof(struct thread_struct, spefscr));

	if (!ret)
		ret = user_regset_copyout(&pos, &count, &kbuf, &ubuf,
					  &target->thread.acc,
					  sizeof(target->thread.evr), -1);

	return ret;
}
