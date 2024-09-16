static inline u64 perf_event_count(struct perf_event *event)
{
	if (event->pmu->count)
		return event->pmu->count(event);

	return __perf_event_count(event);
}
