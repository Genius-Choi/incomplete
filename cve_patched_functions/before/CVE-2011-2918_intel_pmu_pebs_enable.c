static void intel_pmu_pebs_enable(struct perf_event *event)
{
	struct cpu_hw_events *cpuc = &__get_cpu_var(cpu_hw_events);
	struct hw_perf_event *hwc = &event->hw;

	hwc->config &= ~ARCH_PERFMON_EVENTSEL_INT;

	cpuc->pebs_enabled |= 1ULL << hwc->idx;
	WARN_ON_ONCE(cpuc->enabled);

	if (x86_pmu.intel_cap.pebs_trap && event->attr.precise_ip > 1)
		intel_pmu_lbr_enable(event);
}
