static IW_INLINE unsigned int get_raw_sample_4(struct iw_context *ctx,
	   int x, int y)
{
	unsigned short tmpui8;
	tmpui8 = ctx->img1.pixels[y*ctx->img1.bpr + x/2];
	if(x&0x1)
		tmpui8 = tmpui8&0x0f;
	else
		tmpui8 = tmpui8>>4;
	return tmpui8;
}
