static void perf_pmu_rotate_start(struct pmu *pmu)
{
	struct perf_cpu_context *cpuctx = this_cpu_ptr(pmu->pmu_cpu_context);
	struct list_head *head = this_cpu_ptr(&rotation_list);

	WARN_ON(!irqs_disabled());

	if (list_empty(&cpuctx->rotation_list))
		list_add(&cpuctx->rotation_list, head);
}
