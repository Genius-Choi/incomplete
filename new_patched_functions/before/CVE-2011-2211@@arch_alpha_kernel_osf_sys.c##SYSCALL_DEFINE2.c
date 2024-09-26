SYSCALL_DEFINE2(osf_usleep_thread, struct timeval32 __user *, sleep,
		struct timeval32 __user *, remain)
{
	struct timeval tmp;
	unsigned long ticks;

	if (get_tv32(&tmp, sleep))
		goto fault;

	ticks = timeval_to_jiffies(&tmp);

	ticks = schedule_timeout_interruptible(ticks);

	if (remain) {
		jiffies_to_timeval(ticks, &tmp);
		if (put_tv32(remain, &tmp))
			goto fault;
	}
	
	return 0;
 fault:
	return -EFAULT;
}
