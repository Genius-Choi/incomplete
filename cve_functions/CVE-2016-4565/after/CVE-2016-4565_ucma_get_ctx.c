static struct ucma_context *ucma_get_ctx(struct ucma_file *file, int id)
{
	struct ucma_context *ctx;

	mutex_lock(&mut);
	ctx = _ucma_find_context(id, file);
	if (!IS_ERR(ctx)) {
		if (ctx->closing)
			ctx = ERR_PTR(-EIO);
		else
			atomic_inc(&ctx->ref);
	}
	mutex_unlock(&mut);
	return ctx;
}
