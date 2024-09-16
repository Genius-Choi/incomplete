static IW_INLINE void put_raw_sample_8(struct iw_context *ctx, double s,
	   int x, int y, int channel)
{
	iw_byte tmpui8;

	tmpui8 = (iw_byte)(0.5+s);
	ctx->img2.pixels[y*ctx->img2.bpr + ctx->img2_numchannels*x + channel] = tmpui8;
}
