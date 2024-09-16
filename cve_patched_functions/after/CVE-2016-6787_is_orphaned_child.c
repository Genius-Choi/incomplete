static bool is_orphaned_child(struct perf_event *event)
{
	return is_orphaned_event(event->parent);
}
