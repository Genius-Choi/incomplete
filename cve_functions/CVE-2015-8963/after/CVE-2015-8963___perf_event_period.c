static int __perf_event_period(void *info)
{
	struct period_event *pe = info;
	struct perf_event *event = pe->event;
	struct perf_event_context *ctx = event->ctx;
	u64 value = pe->value;
	bool active;

	raw_spin_lock(&ctx->lock);
	if (event->attr.freq) {
		event->attr.sample_freq = value;
	} else {
		event->attr.sample_period = value;
		event->hw.sample_period = value;
	}

	active = (event->state == PERF_EVENT_STATE_ACTIVE);
	if (active) {
		perf_pmu_disable(ctx->pmu);
		event->pmu->stop(event, PERF_EF_UPDATE);
	}

	local64_set(&event->hw.period_left, 0);

	if (active) {
		event->pmu->start(event, PERF_EF_RELOAD);
		perf_pmu_enable(ctx->pmu);
	}
	raw_spin_unlock(&ctx->lock);

	return 0;
}
