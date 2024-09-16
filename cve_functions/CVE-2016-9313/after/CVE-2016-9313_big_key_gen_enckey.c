static inline int big_key_gen_enckey(u8 *key)
{
	return crypto_rng_get_bytes(big_key_rng, key, ENC_KEY_SIZE);
}
