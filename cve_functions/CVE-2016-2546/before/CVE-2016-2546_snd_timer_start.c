int snd_timer_start(struct snd_timer_instance *timeri, unsigned int ticks)
{
	struct snd_timer *timer;
	int result = -EINVAL;
	unsigned long flags;

	if (timeri == NULL || ticks < 1)
		return -EINVAL;
	if (timeri->flags & SNDRV_TIMER_IFLG_SLAVE) {
		result = snd_timer_start_slave(timeri);
		snd_timer_notify1(timeri, SNDRV_TIMER_EVENT_START);
		return result;
	}
	timer = timeri->timer;
	if (timer == NULL)
		return -EINVAL;
	spin_lock_irqsave(&timer->lock, flags);
	timeri->ticks = timeri->cticks = ticks;
	timeri->pticks = 0;
	result = snd_timer_start1(timer, timeri, ticks);
	spin_unlock_irqrestore(&timer->lock, flags);
	snd_timer_notify1(timeri, SNDRV_TIMER_EVENT_START);
	return result;
}
