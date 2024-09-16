int perf_event_release_kernel(struct perf_event *event)
{
	put_event(event);
	return 0;
}
