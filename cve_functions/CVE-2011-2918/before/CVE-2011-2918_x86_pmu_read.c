static inline void x86_pmu_read(struct perf_event *event)
{
	x86_perf_event_update(event);
}
