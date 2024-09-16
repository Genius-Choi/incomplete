static int perf_event_switch_match(struct perf_event *event)
{
	return event->attr.context_switch;
}
