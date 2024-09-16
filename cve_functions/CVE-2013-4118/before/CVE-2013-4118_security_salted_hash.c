static void security_salted_hash(const BYTE* salt, const BYTE* input, int length,
		const BYTE* salt1, const BYTE* salt2, BYTE* output)
{
	CryptoMd5 md5;
	CryptoSha1 sha1;
	BYTE sha1_digest[CRYPTO_SHA1_DIGEST_LENGTH];

	/* SaltedHash(Salt, Input, Salt1, Salt2) = MD5(S + SHA1(Input + Salt + Salt1 + Salt2)) */

	/* SHA1_Digest = SHA1(Input + Salt + Salt1 + Salt2) */
	sha1 = crypto_sha1_init();
	crypto_sha1_update(sha1, input, length); /* Input */
	crypto_sha1_update(sha1, salt, 48); /* Salt (48 bytes) */
	crypto_sha1_update(sha1, salt1, 32); /* Salt1 (32 bytes) */
	crypto_sha1_update(sha1, salt2, 32); /* Salt2 (32 bytes) */
	crypto_sha1_final(sha1, sha1_digest);

	/* SaltedHash(Salt, Input, Salt1, Salt2) = MD5(S + SHA1_Digest) */
	md5 = crypto_md5_init();
	crypto_md5_update(md5, salt, 48); /* Salt (48 bytes) */
	crypto_md5_update(md5, sha1_digest, sizeof(sha1_digest)); /* SHA1_Digest */
	crypto_md5_final(md5, output);
}
