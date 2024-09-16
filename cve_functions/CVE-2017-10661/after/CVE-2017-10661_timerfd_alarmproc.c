static enum alarmtimer_restart timerfd_alarmproc(struct alarm *alarm,
	ktime_t now)
{
	struct timerfd_ctx *ctx = container_of(alarm, struct timerfd_ctx,
					       t.alarm);
	timerfd_triggered(ctx);
	return ALARMTIMER_NORESTART;
}
