xscale1pmu_get_event_idx(struct cpu_hw_events *cpuc,
			struct hw_perf_event *event)
{
	if (XSCALE_PERFCTR_CCNT == event->config_base) {
		if (test_and_set_bit(XSCALE_CYCLE_COUNTER, cpuc->used_mask))
			return -EAGAIN;

		return XSCALE_CYCLE_COUNTER;
	} else {
		if (!test_and_set_bit(XSCALE_COUNTER1, cpuc->used_mask))
			return XSCALE_COUNTER1;

		if (!test_and_set_bit(XSCALE_COUNTER0, cpuc->used_mask))
			return XSCALE_COUNTER0;

		return -EAGAIN;
	}
}
