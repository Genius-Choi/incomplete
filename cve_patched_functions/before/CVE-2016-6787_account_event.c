static void account_event(struct perf_event *event)
{
	if (event->parent)
		return;

	if (event->attach_state & PERF_ATTACH_TASK)
		static_key_slow_inc(&perf_sched_events.key);
	if (event->attr.mmap || event->attr.mmap_data)
		atomic_inc(&nr_mmap_events);
	if (event->attr.comm)
		atomic_inc(&nr_comm_events);
	if (event->attr.task)
		atomic_inc(&nr_task_events);
	if (event->attr.freq) {
		if (atomic_inc_return(&nr_freq_events) == 1)
			tick_nohz_full_kick_all();
	}
	if (has_branch_stack(event))
		static_key_slow_inc(&perf_sched_events.key);
	if (is_cgroup_event(event))
		static_key_slow_inc(&perf_sched_events.key);

	account_event_cpu(event, event->cpu);
}
