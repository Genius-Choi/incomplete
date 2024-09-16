static int perf_event_comm_match(struct perf_event *event)
{
	if (event->state < PERF_EVENT_STATE_INACTIVE)
		return 0;

	if (!event_filter_match(event))
		return 0;

	if (event->attr.comm)
		return 1;

	return 0;
}
