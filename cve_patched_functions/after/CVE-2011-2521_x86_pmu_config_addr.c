static inline unsigned int x86_pmu_config_addr(int index)
{
	return x86_pmu.eventsel + x86_pmu_addr_offset(index);
}
