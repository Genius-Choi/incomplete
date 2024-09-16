static void account_event_cpu(struct perf_event *event, int cpu)
{
	if (event->parent)
		return;

	if (is_cgroup_event(event))
		atomic_inc(&per_cpu(perf_cgroup_events, cpu));
}
