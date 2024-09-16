static int s390_compat_last_break_get(struct task_struct *target,
				      const struct user_regset *regset,
				      unsigned int pos, unsigned int count,
				      void *kbuf, void __user *ubuf)
{
	compat_ulong_t last_break;

	if (count > 0) {
		last_break = task_thread_info(target)->last_break;
		if (kbuf) {
			unsigned long *k = kbuf;
			*k = last_break;
		} else {
			unsigned long  __user *u = ubuf;
			if (__put_user(last_break, u))
				return -EFAULT;
		}
	}
	return 0;
}
