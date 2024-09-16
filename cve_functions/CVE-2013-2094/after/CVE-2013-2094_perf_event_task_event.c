static void perf_event_task_event(struct perf_task_event *task_event)
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
		perf_event_task_ctx(&cpuctx->ctx, task_event);

		ctx = task_event->task_ctx;
		if (!ctx) {
			ctxn = pmu->task_ctx_nr;
			if (ctxn < 0)
				goto next;
			ctx = rcu_dereference(current->perf_event_ctxp[ctxn]);
			if (ctx)
				perf_event_task_ctx(ctx, task_event);
		}
next:
		put_cpu_ptr(pmu->pmu_cpu_context);
	}
	if (task_event->task_ctx)
		perf_event_task_ctx(task_event->task_ctx, task_event);

	rcu_read_unlock();
}
