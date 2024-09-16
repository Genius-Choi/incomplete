static IW_INLINE unsigned int get_raw_sample_16(struct iw_context *ctx,
	   int x, int y, int channel)
{
	size_t z;
	unsigned short tmpui16;
	z = y*ctx->img1.bpr + (ctx->img1_numchannels_physical*x + channel)*2;
	tmpui16 = ( ((unsigned short)(ctx->img1.pixels[z+0])) <<8) | ctx->img1.pixels[z+1];
	return tmpui16;
}
