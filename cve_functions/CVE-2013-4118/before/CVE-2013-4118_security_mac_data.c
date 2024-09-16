void security_mac_data(const BYTE* mac_salt_key, const BYTE* data, UINT32 length,
		BYTE* output)
{
	CryptoMd5 md5;
	CryptoSha1 sha1;
	BYTE length_le[4];
	BYTE sha1_digest[CRYPTO_SHA1_DIGEST_LENGTH];

	/* MacData = MD5(MacSaltKey + pad2 + SHA1(MacSaltKey + pad1 + length + data)) */

	security_UINT32_le(length_le, length); /* length must be little-endian */

	/* SHA1_Digest = SHA1(MacSaltKey + pad1 + length + data) */
	sha1 = crypto_sha1_init();
	crypto_sha1_update(sha1, mac_salt_key, 16); /* MacSaltKey */
	crypto_sha1_update(sha1, pad1, sizeof(pad1)); /* pad1 */
	crypto_sha1_update(sha1, length_le, sizeof(length_le)); /* length */
	crypto_sha1_update(sha1, data, length); /* data */
	crypto_sha1_final(sha1, sha1_digest);

	/* MacData = MD5(MacSaltKey + pad2 + SHA1_Digest) */
	md5 = crypto_md5_init();
	crypto_md5_update(md5, mac_salt_key, 16); /* MacSaltKey */
	crypto_md5_update(md5, pad2, sizeof(pad2)); /* pad2 */
	crypto_md5_update(md5, sha1_digest, sizeof(sha1_digest)); /* SHA1_Digest */
	crypto_md5_final(md5, output);
}
