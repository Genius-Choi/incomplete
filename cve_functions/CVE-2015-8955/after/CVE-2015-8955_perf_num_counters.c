int perf_num_counters(void)
{
	return armpmu_get_max_events();
}
