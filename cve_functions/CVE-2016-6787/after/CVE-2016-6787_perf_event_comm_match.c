static int perf_event_comm_match(struct perf_event *event)
{
	return event->attr.comm;
}
