static enum hrtimer_restart snd_hrtimer_callback(struct hrtimer *hrt)
{
	struct snd_hrtimer *stime = container_of(hrt, struct snd_hrtimer, hrt);
	struct snd_timer *t = stime->timer;
	unsigned long oruns;

	if (!atomic_read(&stime->running))
		return HRTIMER_NORESTART;

	oruns = hrtimer_forward_now(hrt, ns_to_ktime(t->sticks * resolution));
	snd_timer_interrupt(stime->timer, t->sticks * oruns);

	if (!atomic_read(&stime->running))
		return HRTIMER_NORESTART;
	return HRTIMER_RESTART;
}
