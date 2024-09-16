cpu_to_core_group(int cpu, const struct cpumask *cpu_map,
		  struct sched_group **sg, struct cpumask *mask)
{
	int group;
#ifdef CONFIG_SCHED_SMT
	cpumask_and(mask, topology_thread_cpumask(cpu), cpu_map);
	group = cpumask_first(mask);
#else
	group = cpu;
#endif
	if (sg)
		*sg = &per_cpu(sched_group_core, group).sg;
	return group;
}
