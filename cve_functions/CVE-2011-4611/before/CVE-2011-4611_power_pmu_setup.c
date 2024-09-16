static void power_pmu_setup(int cpu)
{
	struct cpu_hw_events *cpuhw = &per_cpu(cpu_hw_events, cpu);

	if (!ppmu)
		return;
	memset(cpuhw, 0, sizeof(*cpuhw));
	cpuhw->mmcr[0] = MMCR0_FC;
}
