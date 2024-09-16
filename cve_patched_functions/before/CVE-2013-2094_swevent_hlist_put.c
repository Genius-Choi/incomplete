static void swevent_hlist_put(struct perf_event *event)
{
	int cpu;

	if (event->cpu != -1) {
		swevent_hlist_put_cpu(event, event->cpu);
		return;
	}

	for_each_possible_cpu(cpu)
		swevent_hlist_put_cpu(event, cpu);
}
