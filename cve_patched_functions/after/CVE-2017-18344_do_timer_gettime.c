static int do_timer_gettime(timer_t timer_id,  struct itimerspec64 *setting)
{
	struct k_itimer *timr;
	const struct k_clock *kc;
	unsigned long flags;
	int ret = 0;

	timr = lock_timer(timer_id, &flags);
	if (!timr)
		return -EINVAL;

	memset(setting, 0, sizeof(*setting));
	kc = timr->kclock;
	if (WARN_ON_ONCE(!kc || !kc->timer_get))
		ret = -EINVAL;
	else
		kc->timer_get(timr, setting);

	unlock_timer(timr, flags);
	return ret;
}
