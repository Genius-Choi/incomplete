int iwpvt_util_randomize(struct iw_prng *prng)
{
	int s;
	s = (int)time(NULL);
	iwpvt_prng_set_random_seed(prng, s);
	return s;
}
