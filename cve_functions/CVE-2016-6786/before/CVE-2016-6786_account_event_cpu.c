static void account_event_cpu(struct perf_event *event, int cpu)
{
	if (event->parent)
		return;

	if (has_branch_stack(event)) {
		if (!(event->attach_state & PERF_ATTACH_TASK))
			atomic_inc(&per_cpu(perf_branch_stack_events, cpu));
	}
	if (is_cgroup_event(event))
		atomic_inc(&per_cpu(perf_cgroup_events, cpu));
}
