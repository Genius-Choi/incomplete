static struct sched_domain *__build_mc_sched_domain(struct s_data *d,
	const struct cpumask *cpu_map, struct sched_domain_attr *attr,
	struct sched_domain *parent, int i)
{
	struct sched_domain *sd = parent;
#ifdef CONFIG_SCHED_MC
	sd = &per_cpu(core_domains, i).sd;
	SD_INIT(sd, MC);
	set_domain_attribute(sd, attr);
	cpumask_and(sched_domain_span(sd), cpu_map, cpu_coregroup_mask(i));
	sd->parent = parent;
	parent->child = sd;
	cpu_to_core_group(i, cpu_map, &sd->groups, d->tmpmask);
#endif
	return sd;
}
