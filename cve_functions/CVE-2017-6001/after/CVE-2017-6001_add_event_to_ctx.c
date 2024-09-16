static void add_event_to_ctx(struct perf_event *event,
			       struct perf_event_context *ctx)
{
	u64 tstamp = perf_event_time(event);

	list_add_event(event, ctx);
	perf_group_attach(event);
	event->tstamp_enabled = tstamp;
	event->tstamp_running = tstamp;
	event->tstamp_stopped = tstamp;
}
