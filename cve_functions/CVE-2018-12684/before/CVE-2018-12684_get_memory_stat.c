get_memory_stat(struct mg_context *ctx)
{
	if (ctx) {
		return &(ctx->ctx_memory);
	}
	return &mg_common_memory;
}
