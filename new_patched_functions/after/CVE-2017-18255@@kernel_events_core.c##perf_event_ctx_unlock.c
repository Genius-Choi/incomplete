static void perf_event_ctx_unlock(struct perf_event *event,
				  struct perf_event_context *ctx)
{
	mutex_unlock(&ctx->mutex);
	put_ctx(ctx);
}
