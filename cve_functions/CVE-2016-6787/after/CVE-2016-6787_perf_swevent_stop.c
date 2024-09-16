static void perf_swevent_stop(struct perf_event *event, int flags)
{
	event->hw.state = PERF_HES_STOPPED;
}
