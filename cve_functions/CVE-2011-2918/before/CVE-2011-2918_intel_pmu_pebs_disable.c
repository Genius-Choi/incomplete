static void intel_pmu_pebs_disable(struct perf_event *event)
{
	struct cpu_hw_events *cpuc = &__get_cpu_var(cpu_hw_events);
	struct hw_perf_event *hwc = &event->hw;

	cpuc->pebs_enabled &= ~(1ULL << hwc->idx);
	if (cpuc->enabled)
		wrmsrl(MSR_IA32_PEBS_ENABLE, cpuc->pebs_enabled);

	hwc->config |= ARCH_PERFMON_EVENTSEL_INT;

	if (x86_pmu.intel_cap.pebs_trap && event->attr.precise_ip > 1)
		intel_pmu_lbr_disable(event);
}
