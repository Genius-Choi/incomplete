static void __init perf_event_init_all_cpus(void)
{
	struct swevent_htable *swhash;
	int cpu;

	for_each_possible_cpu(cpu) {
		swhash = &per_cpu(swevent_htable, cpu);
		mutex_init(&swhash->hlist_mutex);
		INIT_LIST_HEAD(&per_cpu(rotation_list, cpu));
	}
}
