static int cpuset_cpu_inactive(unsigned int cpu)
{
	unsigned long flags;
	struct dl_bw *dl_b;
	bool overflow;
	int cpus;

	if (!cpuhp_tasks_frozen) {
		rcu_read_lock_sched();
		dl_b = dl_bw_of(cpu);

		raw_spin_lock_irqsave(&dl_b->lock, flags);
		cpus = dl_bw_cpus(cpu);
		overflow = __dl_overflow(dl_b, cpus, 0, 0);
		raw_spin_unlock_irqrestore(&dl_b->lock, flags);

		rcu_read_unlock_sched();

		if (overflow)
			return -EBUSY;
		cpuset_update_active_cpus(false);
	} else {
		num_cpus_frozen++;
		partition_sched_domains(1, NULL, NULL);
	}
	return 0;
}
