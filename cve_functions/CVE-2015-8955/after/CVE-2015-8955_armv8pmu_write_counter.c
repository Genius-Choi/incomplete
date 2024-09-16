static inline void armv8pmu_write_counter(int idx, u32 value)
{
	if (!armv8pmu_counter_valid(idx))
		pr_err("CPU%u writing wrong counter %d\n",
			smp_processor_id(), idx);
	else if (idx == ARMV8_IDX_CYCLE_COUNTER)
		asm volatile("msr pmccntr_el0, %0" :: "r" (value));
	else if (armv8pmu_select_counter(idx) == idx)
		asm volatile("msr pmxevcntr_el0, %0" :: "r" (value));
}
