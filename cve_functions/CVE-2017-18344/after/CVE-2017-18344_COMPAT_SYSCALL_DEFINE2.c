COMPAT_SYSCALL_DEFINE2(clock_getres, clockid_t, which_clock,
		       struct compat_timespec __user *, tp)
{
	const struct k_clock *kc = clockid_to_kclock(which_clock);
	struct timespec64 ts;
	int err;

	if (!kc)
		return -EINVAL;

	err = kc->clock_getres(which_clock, &ts);
	if (!err && tp && compat_put_timespec64(&ts, tp))
		return -EFAULT;

	return err;
}
