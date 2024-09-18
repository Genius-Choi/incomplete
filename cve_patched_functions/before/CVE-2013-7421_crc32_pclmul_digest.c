static int crc32_pclmul_digest(struct shash_desc *desc, const u8 *data,
			       unsigned int len, u8 *out)
{
	return __crc32_pclmul_finup(crypto_shash_ctx(desc->tfm), data, len,
				    out);
}
