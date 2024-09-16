static int fpa_set(struct task_struct *target,
		   const struct user_regset *regset,
		   unsigned int pos, unsigned int count,
		   const void *kbuf, const void __user *ubuf)
{
	struct thread_info *thread = task_thread_info(target);

	thread->used_cp[1] = thread->used_cp[2] = 1;

	return user_regset_copyin(&pos, &count, &kbuf, &ubuf,
		&thread->fpstate,
		0, sizeof(struct user_fp));
}
