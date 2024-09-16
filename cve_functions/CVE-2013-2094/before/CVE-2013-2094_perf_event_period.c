static int perf_event_period(struct perf_event *event, u64 __user *arg)
{
	struct perf_event_context *ctx = event->ctx;
	int ret = 0;
	u64 value;

	if (!is_sampling_event(event))
		return -EINVAL;

	if (copy_from_user(&value, arg, sizeof(value)))
		return -EFAULT;

	if (!value)
		return -EINVAL;

	raw_spin_lock_irq(&ctx->lock);
	if (event->attr.freq) {
		if (value > sysctl_perf_event_sample_rate) {
			ret = -EINVAL;
			goto unlock;
		}

		event->attr.sample_freq = value;
	} else {
		event->attr.sample_period = value;
		event->hw.sample_period = value;
	}
unlock:
	raw_spin_unlock_irq(&ctx->lock);

	return ret;
}
