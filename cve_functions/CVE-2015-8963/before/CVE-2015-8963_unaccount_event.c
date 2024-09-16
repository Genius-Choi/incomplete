static void unaccount_event(struct perf_event *event)
{
	if (event->parent)
		return;

	if (event->attach_state & PERF_ATTACH_TASK)
		static_key_slow_dec_deferred(&perf_sched_events);
	if (event->attr.mmap || event->attr.mmap_data)
		atomic_dec(&nr_mmap_events);
	if (event->attr.comm)
		atomic_dec(&nr_comm_events);
	if (event->attr.task)
		atomic_dec(&nr_task_events);
	if (event->attr.freq)
		atomic_dec(&nr_freq_events);
	if (event->attr.context_switch) {
		static_key_slow_dec_deferred(&perf_sched_events);
		atomic_dec(&nr_switch_events);
	}
	if (is_cgroup_event(event))
		static_key_slow_dec_deferred(&perf_sched_events);
	if (has_branch_stack(event))
		static_key_slow_dec_deferred(&perf_sched_events);

	unaccount_event_cpu(event, event->cpu);
}
