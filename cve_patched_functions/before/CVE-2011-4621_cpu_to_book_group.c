cpu_to_book_group(int cpu, const struct cpumask *cpu_map,
		  struct sched_group **sg, struct cpumask *mask)
{
	int group = cpu;
#ifdef CONFIG_SCHED_MC
	cpumask_and(mask, cpu_coregroup_mask(cpu), cpu_map);
	group = cpumask_first(mask);
#elif defined(CONFIG_SCHED_SMT)
	cpumask_and(mask, topology_thread_cpumask(cpu), cpu_map);
	group = cpumask_first(mask);
#endif
	if (sg)
		*sg = &per_cpu(sched_group_book, group).sg;
	return group;
}
