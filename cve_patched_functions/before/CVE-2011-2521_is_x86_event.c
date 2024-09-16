static inline int is_x86_event(struct perf_event *event)
{
	return event->pmu == &pmu;
}
