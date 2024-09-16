static void perf_event_exit_cpu_context(int cpu)
{
	struct perf_event_context *ctx;
	struct pmu *pmu;
	int idx;

	idx = srcu_read_lock(&pmus_srcu);
	list_for_each_entry_rcu(pmu, &pmus, entry) {
		ctx = &per_cpu_ptr(pmu->pmu_cpu_context, cpu)->ctx;

		mutex_lock(&ctx->mutex);
		smp_call_function_single(cpu, __perf_event_exit_context, ctx, 1);
		mutex_unlock(&ctx->mutex);
	}
	srcu_read_unlock(&pmus_srcu, idx);
}
