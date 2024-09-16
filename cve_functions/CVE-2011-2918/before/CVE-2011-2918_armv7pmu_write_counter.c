static inline void armv7pmu_write_counter(int idx, u32 value)
{
	if (idx == ARMV7_CYCLE_COUNTER)
		asm volatile("mcr p15, 0, %0, c9, c13, 0" : : "r" (value));
	else if ((idx >= ARMV7_COUNTER0) && (idx <= ARMV7_COUNTER_LAST)) {
		if (armv7_pmnc_select_counter(idx) == idx)
			asm volatile("mcr p15, 0, %0, c9, c13, 2"
				     : : "r" (value));
	} else
		pr_err("CPU%u writing wrong counter %d\n",
			smp_processor_id(), idx);
}
