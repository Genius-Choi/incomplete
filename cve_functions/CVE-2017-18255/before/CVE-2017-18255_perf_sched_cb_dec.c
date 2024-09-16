void perf_sched_cb_dec(struct pmu *pmu)
{
	struct perf_cpu_context *cpuctx = this_cpu_ptr(pmu->pmu_cpu_context);

	this_cpu_dec(perf_sched_cb_usages);

	if (!--cpuctx->sched_cb_usage)
		list_del(&cpuctx->sched_cb_entry);
}
