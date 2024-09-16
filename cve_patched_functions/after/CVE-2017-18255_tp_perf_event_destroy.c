static void tp_perf_event_destroy(struct perf_event *event)
{
	perf_trace_destroy(event);
}
