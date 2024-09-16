static struct perf_cpu_context __percpu *find_pmu_context(int ctxn)
{
	struct pmu *pmu;

	if (ctxn < 0)
		return NULL;

	list_for_each_entry(pmu, &pmus, entry) {
		if (pmu->task_ctx_nr == ctxn)
			return pmu->pmu_cpu_context;
	}

	return NULL;
}
