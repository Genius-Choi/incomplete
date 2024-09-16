static struct pmu_hw_events *armpmu_get_cpu_events(void)
{
	return this_cpu_ptr(&cpu_hw_events);
}
