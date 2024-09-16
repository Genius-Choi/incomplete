static int s390_system_call_get(struct task_struct *target,
				const struct user_regset *regset,
				unsigned int pos, unsigned int count,
				void *kbuf, void __user *ubuf)
{
	unsigned int *data = &task_thread_info(target)->system_call;
	return user_regset_copyout(&pos, &count, &kbuf, &ubuf,
				   data, 0, sizeof(unsigned int));
}
