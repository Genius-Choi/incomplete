static void start_cpu_timer(int cpu)
{
	struct delayed_work *reap_work = &per_cpu(slab_reap_work, cpu);

	if (reap_work->work.func == NULL) {
		init_reap_node(cpu);
		INIT_DEFERRABLE_WORK(reap_work, cache_reap);
		schedule_delayed_work_on(cpu, reap_work,
					__round_jiffies_relative(HZ, cpu));
	}
}
