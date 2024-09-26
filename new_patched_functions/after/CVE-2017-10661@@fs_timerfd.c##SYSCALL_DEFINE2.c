SYSCALL_DEFINE2(timerfd_gettime, int, ufd, struct itimerspec __user *, otmr)
{
	struct itimerspec kotmr;
	int ret = do_timerfd_gettime(ufd, &kotmr);
	if (ret)
		return ret;
	return copy_to_user(otmr, &kotmr, sizeof(kotmr)) ? -EFAULT: 0;
}
