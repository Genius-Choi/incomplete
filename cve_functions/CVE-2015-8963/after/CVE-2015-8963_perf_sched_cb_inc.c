void perf_sched_cb_inc(struct pmu *pmu)
{
	this_cpu_inc(perf_sched_cb_usages);
}
