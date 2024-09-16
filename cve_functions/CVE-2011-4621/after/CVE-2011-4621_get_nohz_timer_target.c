int get_nohz_timer_target(void)
{
	int cpu = smp_processor_id();
	int i;
	struct sched_domain *sd;

	for_each_domain(cpu, sd) {
		for_each_cpu(i, sched_domain_span(sd))
			if (!idle_cpu(i))
				return i;
	}
	return cpu;
}
