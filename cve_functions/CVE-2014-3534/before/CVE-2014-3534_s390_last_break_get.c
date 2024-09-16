static int s390_last_break_get(struct task_struct *target,
			       const struct user_regset *regset,
			       unsigned int pos, unsigned int count,
			       void *kbuf, void __user *ubuf)
{
	if (count > 0) {
		if (kbuf) {
			unsigned long *k = kbuf;
			*k = task_thread_info(target)->last_break;
		} else {
			unsigned long  __user *u = ubuf;
			if (__put_user(task_thread_info(target)->last_break, u))
				return -EFAULT;
		}
	}
	return 0;
}
