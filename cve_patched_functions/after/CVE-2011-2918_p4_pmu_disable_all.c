static void p4_pmu_disable_all(void)
{
	struct cpu_hw_events *cpuc = &__get_cpu_var(cpu_hw_events);
	int idx;

	for (idx = 0; idx < x86_pmu.num_counters; idx++) {
		struct perf_event *event = cpuc->events[idx];
		if (!test_bit(idx, cpuc->active_mask))
			continue;
		p4_pmu_disable_event(event);
	}

	p4_pmu_disable_pebs();
}
