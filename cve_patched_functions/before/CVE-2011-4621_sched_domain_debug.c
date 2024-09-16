static void sched_domain_debug(struct sched_domain *sd, int cpu)
{
	cpumask_var_t groupmask;
	int level = 0;

	if (!sched_domain_debug_enabled)
		return;

	if (!sd) {
		printk(KERN_DEBUG "CPU%d attaching NULL sched-domain.\n", cpu);
		return;
	}

	printk(KERN_DEBUG "CPU%d attaching sched-domain:\n", cpu);

	if (!alloc_cpumask_var(&groupmask, GFP_KERNEL)) {
		printk(KERN_DEBUG "Cannot load-balance (out of memory)\n");
		return;
	}

	for (;;) {
		if (sched_domain_debug_one(sd, cpu, level, groupmask))
			break;
		level++;
		sd = sd->parent;
		if (!sd)
			break;
	}
	free_cpumask_var(groupmask);
}
