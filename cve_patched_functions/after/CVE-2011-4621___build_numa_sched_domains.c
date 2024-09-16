static struct sched_domain *__build_numa_sched_domains(struct s_data *d,
	const struct cpumask *cpu_map, struct sched_domain_attr *attr, int i)
{
	struct sched_domain *sd = NULL;
#ifdef CONFIG_NUMA
	struct sched_domain *parent;

	d->sd_allnodes = 0;
	if (cpumask_weight(cpu_map) >
	    SD_NODES_PER_DOMAIN * cpumask_weight(d->nodemask)) {
		sd = &per_cpu(allnodes_domains, i).sd;
		SD_INIT(sd, ALLNODES);
		set_domain_attribute(sd, attr);
		cpumask_copy(sched_domain_span(sd), cpu_map);
		cpu_to_allnodes_group(i, cpu_map, &sd->groups, d->tmpmask);
		d->sd_allnodes = 1;
	}
	parent = sd;

	sd = &per_cpu(node_domains, i).sd;
	SD_INIT(sd, NODE);
	set_domain_attribute(sd, attr);
	sched_domain_node_span(cpu_to_node(i), sched_domain_span(sd));
	sd->parent = parent;
	if (parent)
		parent->child = sd;
	cpumask_and(sched_domain_span(sd), sched_domain_span(sd), cpu_map);
#endif
	return sd;
}
