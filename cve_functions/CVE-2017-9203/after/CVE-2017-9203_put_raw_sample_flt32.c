static void put_raw_sample_flt32(struct iw_context *ctx, double s,
	   int x, int y, int channel)
{
	size_t pos;
	pos = y*ctx->img2.bpr + (ctx->img2_numchannels*x + channel)*4;
	iw_put_float32(&ctx->img2.pixels[pos], (iw_float32)s);
}
