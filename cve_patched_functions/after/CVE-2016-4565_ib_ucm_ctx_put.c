static void ib_ucm_ctx_put(struct ib_ucm_context *ctx)
{
	if (atomic_dec_and_test(&ctx->ref))
		complete(&ctx->comp);
}
