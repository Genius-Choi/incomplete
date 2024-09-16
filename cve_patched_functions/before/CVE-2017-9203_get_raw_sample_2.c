static IW_INLINE unsigned int get_raw_sample_2(struct iw_context *ctx,
	   int x, int y)
{
	unsigned short tmpui8;
	tmpui8 = ctx->img1.pixels[y*ctx->img1.bpr + x/4];
	tmpui8 = ( tmpui8 >> ((3-x%4)*2) ) & 0x03;
	return tmpui8;
}
