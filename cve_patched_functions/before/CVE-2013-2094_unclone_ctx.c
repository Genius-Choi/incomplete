static void unclone_ctx(struct perf_event_context *ctx)
{
	if (ctx->parent_ctx) {
		put_ctx(ctx->parent_ctx);
		ctx->parent_ctx = NULL;
	}
}
