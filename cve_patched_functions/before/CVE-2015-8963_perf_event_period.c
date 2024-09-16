static int perf_event_period(struct perf_event *event, u64 __user *arg)
{
	struct period_event pe = { .event = event, };
	struct perf_event_context *ctx = event->ctx;
	struct task_struct *task;
	u64 value;

	if (!is_sampling_event(event))
		return -EINVAL;

	if (copy_from_user(&value, arg, sizeof(value)))
		return -EFAULT;

	if (!value)
		return -EINVAL;

	if (event->attr.freq && value > sysctl_perf_event_sample_rate)
		return -EINVAL;

	task = ctx->task;
	pe.value = value;

	if (!task) {
		cpu_function_call(event->cpu, __perf_event_period, &pe);
		return 0;
	}

retry:
	if (!task_function_call(task, __perf_event_period, &pe))
		return 0;

	raw_spin_lock_irq(&ctx->lock);
	if (ctx->is_active) {
		raw_spin_unlock_irq(&ctx->lock);
		task = ctx->task;
		goto retry;
	}

	if (event->attr.freq) {
		event->attr.sample_freq = value;
	} else {
		event->attr.sample_period = value;
		event->hw.sample_period = value;
	}

	local64_set(&event->hw.period_left, 0);
	raw_spin_unlock_irq(&ctx->lock);

	return 0;
}
