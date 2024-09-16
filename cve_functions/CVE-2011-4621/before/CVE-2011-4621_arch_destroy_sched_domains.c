static void arch_destroy_sched_domains(const struct cpumask *cpu_map,
				       struct cpumask *tmpmask)
{
	free_sched_groups(cpu_map, tmpmask);
}
