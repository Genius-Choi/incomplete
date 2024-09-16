cpu_pmu_reset(void)
{
	if (cpu_pmu && cpu_pmu->reset)
		return on_each_cpu(cpu_pmu->reset, NULL, 1);
	return 0;
}
