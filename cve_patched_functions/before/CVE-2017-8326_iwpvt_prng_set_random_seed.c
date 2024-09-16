void iwpvt_prng_set_random_seed(struct iw_prng *prng, int s)
{
	prng->multiply = ((iw_uint32)0x03333333) + s;
	prng->carry    = ((iw_uint32)0x05555555) + s;
}
