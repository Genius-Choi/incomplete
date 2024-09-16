int crypto_has_skcipher2(const char *alg_name, u32 type, u32 mask)
{
	return crypto_type_has_alg(alg_name, &crypto_skcipher_type2,
				   type, mask);
}
