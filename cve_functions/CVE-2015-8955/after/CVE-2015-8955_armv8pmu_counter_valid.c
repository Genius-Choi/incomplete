static inline int armv8pmu_counter_valid(int idx)
{
	return idx >= ARMV8_IDX_CYCLE_COUNTER && idx <= ARMV8_IDX_COUNTER_LAST;
}
