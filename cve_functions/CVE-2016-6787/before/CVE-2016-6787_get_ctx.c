static void get_ctx(struct perf_event_context *ctx)
{
	WARN_ON(!atomic_inc_not_zero(&ctx->refcount));
}
