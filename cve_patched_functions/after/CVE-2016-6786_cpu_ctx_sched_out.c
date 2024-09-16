static void cpu_ctx_sched_out(struct perf_cpu_context *cpuctx,
			      enum event_type_t event_type)
{
	ctx_sched_out(&cpuctx->ctx, cpuctx, event_type);
}
