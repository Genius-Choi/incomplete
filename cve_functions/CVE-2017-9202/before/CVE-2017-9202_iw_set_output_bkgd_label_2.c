IW_IMPL(void) iw_set_output_bkgd_label_2(struct iw_context *ctx, const struct iw_color *clr)
{
	ctx->req.output_bkgd_label_valid = 1;
	ctx->req.output_bkgd_label = *clr;
}
