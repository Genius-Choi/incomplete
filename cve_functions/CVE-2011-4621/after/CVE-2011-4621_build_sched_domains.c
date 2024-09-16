static int build_sched_domains(const struct cpumask *cpu_map)
{
	return __build_sched_domains(cpu_map, NULL);
}
