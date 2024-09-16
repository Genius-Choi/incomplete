static void timerfd_show(struct seq_file *m, struct file *file)
{
	struct timerfd_ctx *ctx = file->private_data;
	struct itimerspec t;

	spin_lock_irq(&ctx->wqh.lock);
	t.it_value = ktime_to_timespec(timerfd_get_remaining(ctx));
	t.it_interval = ktime_to_timespec(ctx->tintv);
	spin_unlock_irq(&ctx->wqh.lock);

	seq_printf(m,
		   "clockid: %d\n"
		   "ticks: %llu\n"
		   "settime flags: 0%o\n"
		   "it_value: (%llu, %llu)\n"
		   "it_interval: (%llu, %llu)\n",
		   ctx->clockid,
		   (unsigned long long)ctx->ticks,
		   ctx->settime_flags,
		   (unsigned long long)t.it_value.tv_sec,
		   (unsigned long long)t.it_value.tv_nsec,
		   (unsigned long long)t.it_interval.tv_sec,
		   (unsigned long long)t.it_interval.tv_nsec);
}
