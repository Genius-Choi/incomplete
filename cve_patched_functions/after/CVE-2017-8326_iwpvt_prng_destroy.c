void iwpvt_prng_destroy(struct iw_context *ctx, struct iw_prng *prng)
{
	if(prng) iw_free(ctx,(void*)prng);
}
