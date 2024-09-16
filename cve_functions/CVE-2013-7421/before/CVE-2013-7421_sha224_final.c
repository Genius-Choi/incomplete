static int sha224_final(struct shash_desc *desc, u8 *hash)
{
	u8 D[SHA256_DIGEST_SIZE];

	sha256_final(desc, D);

	memcpy(hash, D, SHA224_DIGEST_SIZE);
	memzero_explicit(D, SHA256_DIGEST_SIZE);

	return 0;
}
