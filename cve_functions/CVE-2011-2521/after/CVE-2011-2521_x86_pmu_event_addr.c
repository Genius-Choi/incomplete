static inline unsigned int x86_pmu_event_addr(int index)
{
	return x86_pmu.perfctr + x86_pmu_addr_offset(index);
}
