struct iw_prng *iwpvt_prng_create(struct iw_context *ctx)
{
	struct iw_prng *prng;
	prng = (struct iw_prng*)iw_mallocz(ctx,sizeof(struct iw_prng));
	if(!prng) return NULL;
	return prng;
}
