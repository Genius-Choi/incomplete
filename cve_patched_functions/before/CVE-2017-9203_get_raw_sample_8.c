static IW_INLINE unsigned int get_raw_sample_8(struct iw_context *ctx,
	   int x, int y, int channel)
{
	unsigned short tmpui8;
	tmpui8 = ctx->img1.pixels[y*ctx->img1.bpr + ctx->img1_numchannels_physical*x + channel];
	return tmpui8;
}
