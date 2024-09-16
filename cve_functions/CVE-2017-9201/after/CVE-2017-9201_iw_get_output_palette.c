IW_IMPL(const struct iw_palette*) iw_get_output_palette(struct iw_context *ctx)
{
	return ctx->optctx.palette;
}
