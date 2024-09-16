static bool is_kernel_event(struct perf_event *event)
{
	return event->owner == EVENT_OWNER_KERNEL;
}
