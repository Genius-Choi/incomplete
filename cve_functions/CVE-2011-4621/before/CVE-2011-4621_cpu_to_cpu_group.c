cpu_to_cpu_group(int cpu, const struct cpumask *cpu_map,
		 struct sched_group **sg, struct cpumask *unused)
{
	if (sg)
		*sg = &per_cpu(sched_groups, cpu).sg;
	return cpu;
}
