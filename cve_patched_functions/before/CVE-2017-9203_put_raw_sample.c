static void put_raw_sample(struct iw_context *ctx, double s,
	   int x, int y, int channel)
{
	switch(ctx->img2.bit_depth) {
	case 8:  put_raw_sample_8(ctx,s,x,y,channel); break;
	case 16: put_raw_sample_16(ctx,s,x,y,channel); break;
	}
}
