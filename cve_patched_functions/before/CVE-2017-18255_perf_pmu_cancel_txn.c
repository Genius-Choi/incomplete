static void perf_pmu_cancel_txn(struct pmu *pmu)
{
	unsigned int flags =  __this_cpu_read(nop_txn_flags);

	__this_cpu_write(nop_txn_flags, 0);

	if (flags & ~PERF_PMU_TXN_ADD)
		return;

	perf_pmu_enable(pmu);
}
