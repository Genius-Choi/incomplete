static void iw_set_out_channeltypes(struct iw_context *ctx)
{
	int i;
	for(i=0;i<ctx->img2_numchannels;i++) {
		ctx->img2_ci[i].channeltype = iw_get_channeltype(ctx->img2.imgtype,i);
	}
}
