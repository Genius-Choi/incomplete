static int perf_event_task_match(struct perf_event *event)
{
	if (event->state < PERF_EVENT_STATE_INACTIVE)
		return 0;

	if (!event_filter_match(event))
		return 0;

	if (event->attr.comm || event->attr.mmap ||
	    event->attr.mmap_data || event->attr.task)
		return 1;

	return 0;
}
