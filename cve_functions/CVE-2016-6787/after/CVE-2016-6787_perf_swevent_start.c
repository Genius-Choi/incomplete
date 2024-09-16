static void perf_swevent_start(struct perf_event *event, int flags)
{
	event->hw.state = 0;
}
