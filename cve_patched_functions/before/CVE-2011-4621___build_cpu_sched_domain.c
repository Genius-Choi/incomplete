static struct sched_domain *__build_cpu_sched_domain(struct s_data *d,
	const struct cpumask *cpu_map, struct sched_domain_attr *attr,
	struct sched_domain *parent, int i)
{
	struct sched_domain *sd;
	sd = &per_cpu(phys_domains, i).sd;
	SD_INIT(sd, CPU);
	set_domain_attribute(sd, attr);
	cpumask_copy(sched_domain_span(sd), d->nodemask);
	sd->parent = parent;
	if (parent)
		parent->child = sd;
	cpu_to_phys_group(i, cpu_map, &sd->groups, d->tmpmask);
	return sd;
}
