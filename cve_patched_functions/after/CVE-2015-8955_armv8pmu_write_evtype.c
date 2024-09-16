static inline void armv8pmu_write_evtype(int idx, u32 val)
{
	if (armv8pmu_select_counter(idx) == idx) {
		val &= ARMV8_EVTYPE_MASK;
		asm volatile("msr pmxevtyper_el0, %0" :: "r" (val));
	}
}
