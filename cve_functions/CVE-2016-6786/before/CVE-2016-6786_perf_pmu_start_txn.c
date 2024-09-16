static void perf_pmu_start_txn(struct pmu *pmu)
{
	perf_pmu_disable(pmu);
}
