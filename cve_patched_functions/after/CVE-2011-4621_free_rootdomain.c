static void free_rootdomain(struct root_domain *rd)
{
	synchronize_sched();

	cpupri_cleanup(&rd->cpupri);

	free_cpumask_var(rd->rto_mask);
	free_cpumask_var(rd->online);
	free_cpumask_var(rd->span);
	kfree(rd);
}
