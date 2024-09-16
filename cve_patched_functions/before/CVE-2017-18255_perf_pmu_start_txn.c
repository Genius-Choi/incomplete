static void perf_pmu_start_txn(struct pmu *pmu, unsigned int flags)
{
	__this_cpu_write(nop_txn_flags, flags);

	if (flags & ~PERF_PMU_TXN_ADD)
		return;

	perf_pmu_disable(pmu);
}
