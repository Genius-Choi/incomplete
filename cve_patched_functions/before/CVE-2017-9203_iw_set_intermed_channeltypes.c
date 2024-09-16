static void iw_set_intermed_channeltypes(struct iw_context *ctx)
{
	int i;
	for(i=0;i<ctx->intermed_numchannels;i++) {
		ctx->intermed_ci[i].channeltype = iw_get_channeltype(ctx->intermed_imgtype,i);
	}
}
