static void _perf_event_reset(struct perf_event *event)
{
	(void)perf_event_read(event, false);
	local64_set(&event->count, 0);
	perf_event_update_userpage(event);
}
