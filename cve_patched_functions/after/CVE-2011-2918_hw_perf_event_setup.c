void hw_perf_event_setup(int cpu)
{
	struct cpu_hw_events *cpuhw = &per_cpu(cpu_hw_events, cpu);

	memset(cpuhw, 0, sizeof(*cpuhw));
}
