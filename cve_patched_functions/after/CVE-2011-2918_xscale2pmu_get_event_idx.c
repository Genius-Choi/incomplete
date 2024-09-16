xscale2pmu_get_event_idx(struct cpu_hw_events *cpuc,
			struct hw_perf_event *event)
{
	int idx = xscale1pmu_get_event_idx(cpuc, event);
	if (idx >= 0)
		goto out;

	if (!test_and_set_bit(XSCALE_COUNTER3, cpuc->used_mask))
		idx = XSCALE_COUNTER3;
	else if (!test_and_set_bit(XSCALE_COUNTER2, cpuc->used_mask))
		idx = XSCALE_COUNTER2;
out:
	return idx;
}
