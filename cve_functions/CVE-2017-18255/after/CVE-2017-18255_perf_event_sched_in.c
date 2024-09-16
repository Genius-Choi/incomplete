static void perf_event_sched_in(struct perf_cpu_context *cpuctx,
				struct perf_event_context *ctx,
				struct task_struct *task)
{
	cpu_ctx_sched_in(cpuctx, EVENT_PINNED, task);
	if (ctx)
		ctx_sched_in(ctx, cpuctx, EVENT_PINNED, task);
	cpu_ctx_sched_in(cpuctx, EVENT_FLEXIBLE, task);
	if (ctx)
		ctx_sched_in(ctx, cpuctx, EVENT_FLEXIBLE, task);
}
