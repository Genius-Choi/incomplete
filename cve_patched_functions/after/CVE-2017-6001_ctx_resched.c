static void ctx_resched(struct perf_cpu_context *cpuctx,
			struct perf_event_context *task_ctx)
{
	perf_pmu_disable(cpuctx->ctx.pmu);
	if (task_ctx)
		task_ctx_sched_out(cpuctx, task_ctx);
	cpu_ctx_sched_out(cpuctx, EVENT_ALL);
	perf_event_sched_in(cpuctx, task_ctx, current);
	perf_pmu_enable(cpuctx->ctx.pmu);
}
