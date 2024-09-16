static int armv8_pmuv3_map_event(struct perf_event *event)
{
	return map_cpu_event(event, &armv8_pmuv3_perf_map,
				&armv8_pmuv3_perf_cache_map,
				ARMV8_EVTYPE_EVENT);
}
