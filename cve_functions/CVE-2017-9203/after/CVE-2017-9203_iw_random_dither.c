static int iw_random_dither(struct iw_context *ctx, double fraction, int x, int y,
	int dithersubtype, int channel)
{
	double threshold;

	threshold = ((double)iwpvt_prng_rand(ctx->prng)) / (double)0xffffffff;
	if(fraction>=threshold) return 1;
	return 0;
}
