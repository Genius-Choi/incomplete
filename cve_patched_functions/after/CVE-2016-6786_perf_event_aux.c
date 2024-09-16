perf_event_aux(perf_event_aux_output_cb output, void *data,
	       struct perf_event_context *task_ctx)
{
	struct perf_cpu_context *cpuctx;
	struct perf_event_context *ctx;
	struct pmu *pmu;
	int ctxn;

	rcu_read_lock();
	list_for_each_entry_rcu(pmu, &pmus, entry) {
		cpuctx = get_cpu_ptr(pmu->pmu_cpu_context);
		if (cpuctx->unique_pmu != pmu)
			goto next;
		perf_event_aux_ctx(&cpuctx->ctx, output, data);
		if (task_ctx)
			goto next;
		ctxn = pmu->task_ctx_nr;
		if (ctxn < 0)
			goto next;
		ctx = rcu_dereference(current->perf_event_ctxp[ctxn]);
		if (ctx)
			perf_event_aux_ctx(ctx, output, data);
next:
		put_cpu_ptr(pmu->pmu_cpu_context);
	}

	if (task_ctx) {
		preempt_disable();
		perf_event_aux_ctx(task_ctx, output, data);
		preempt_enable();
	}
	rcu_read_unlock();
}
