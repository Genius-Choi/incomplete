static void perf_pmu_rotate_stop(struct pmu *pmu)
{
	struct perf_cpu_context *cpuctx = this_cpu_ptr(pmu->pmu_cpu_context);

	WARN_ON(!irqs_disabled());

	list_del_init(&cpuctx->rotation_list);
}
