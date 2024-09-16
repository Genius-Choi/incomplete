intel_bts_constraints(struct perf_event *event)
{
	struct hw_perf_event *hwc = &event->hw;
	unsigned int hw_event, bts_event;

	if (event->attr.freq)
		return NULL;

	hw_event = hwc->config & INTEL_ARCH_EVENT_MASK;
	bts_event = x86_pmu.event_map(PERF_COUNT_HW_BRANCH_INSTRUCTIONS);

	if (unlikely(hw_event == bts_event && hwc->sample_period == 1))
		return &bts_constraint;

	return NULL;
}
