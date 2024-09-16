COMPAT_SYSCALL_DEFINE4(timerfd_settime, int, ufd, int, flags,
		const struct compat_itimerspec __user *, utmr,
		struct compat_itimerspec __user *, otmr)
{
	struct itimerspec new, old;
	int ret;

	if (get_compat_itimerspec(&new, utmr))
		return -EFAULT;
	ret = do_timerfd_settime(ufd, flags, &new, &old);
	if (ret)
		return ret;
	if (otmr && put_compat_itimerspec(otmr, &old))
		return -EFAULT;
	return ret;
}
