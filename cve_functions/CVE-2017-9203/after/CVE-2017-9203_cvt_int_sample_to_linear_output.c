static iw_tmpsample cvt_int_sample_to_linear_output(struct iw_context *ctx,
	unsigned int v, const struct iw_csdescr *csdescr, double overall_maxcolorcode)
{
	iw_tmpsample s;

	if(csdescr->cstype==IW_CSTYPE_LINEAR) {
		return ((double)v) / overall_maxcolorcode;
	}
	else if(ctx->output_rev_color_corr_table) {
		return ctx->output_rev_color_corr_table[v];
	}

	s = ((double)v) / overall_maxcolorcode;
	return x_to_linear_sample(s,csdescr);
}
