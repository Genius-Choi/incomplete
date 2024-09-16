static void iw_set_input_channeltypes(struct iw_context *ctx)
{
	int i;
	for(i=0;i<ctx->img1_numchannels_logical;i++) {
		ctx->img1_ci[i].channeltype = iw_get_channeltype(ctx->img1_imgtype_logical,i);
	}
}
