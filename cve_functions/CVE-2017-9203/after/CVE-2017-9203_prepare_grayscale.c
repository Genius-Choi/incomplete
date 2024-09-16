static void prepare_grayscale(struct iw_context *ctx)
{
	switch(ctx->grayscale_formula) {
	case IW_GSF_STANDARD:
		ctx->grayscale_formula = IW_GSF_WEIGHTED;
		iw_set_grayscale_weights(ctx,0.212655,0.715158,0.072187);
		break;
	case IW_GSF_COMPATIBLE:
		ctx->grayscale_formula = IW_GSF_WEIGHTED;
		iw_set_grayscale_weights(ctx,0.299,0.587,0.114);
		break;
	}
}
