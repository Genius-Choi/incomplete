static void perf_ctx_lock(struct perf_cpu_context *cpuctx,
			  struct perf_event_context *ctx)
{
	raw_spin_lock(&cpuctx->ctx.lock);
	if (ctx)
		raw_spin_lock(&ctx->lock);
}
