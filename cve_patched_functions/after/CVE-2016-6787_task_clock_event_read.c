static void task_clock_event_read(struct perf_event *event)
{
	u64 now = perf_clock();
	u64 delta = now - event->ctx->timestamp;
	u64 time = event->ctx->time + delta;

	task_clock_event_update(event, time);
}
