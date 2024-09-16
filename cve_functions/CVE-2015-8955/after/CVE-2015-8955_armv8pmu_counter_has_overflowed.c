static inline int armv8pmu_counter_has_overflowed(u32 pmnc, int idx)
{
	int ret = 0;
	u32 counter;

	if (!armv8pmu_counter_valid(idx)) {
		pr_err("CPU%u checking wrong counter %d overflow status\n",
			smp_processor_id(), idx);
	} else {
		counter = ARMV8_IDX_TO_COUNTER(idx);
		ret = pmnc & BIT(counter);
	}

	return ret;
}
