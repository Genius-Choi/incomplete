static IW_INLINE unsigned int get_raw_sample_1(struct iw_context *ctx,
	   int x, int y)
{
	unsigned short tmpui8;
	tmpui8 = ctx->img1.pixels[y*ctx->img1.bpr + x/8];
	if(tmpui8 & (1<<(7-x%8))) return 1;
	return 0;
}
