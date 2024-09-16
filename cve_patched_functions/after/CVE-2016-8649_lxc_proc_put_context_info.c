static void lxc_proc_put_context_info(struct lxc_proc_context_info *ctx)
{
	free(ctx->lsm_label);
	if (ctx->container)
		lxc_container_put(ctx->container);
	free(ctx);
}
