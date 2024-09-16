void security_hmac_signature(const BYTE* data, int length, BYTE* output, rdpRdp* rdp)
{
	BYTE buf[20];
	BYTE use_count_le[4];

	security_UINT32_le(use_count_le, rdp->encrypt_use_count);

	crypto_hmac_sha1_init(rdp->fips_hmac, rdp->fips_sign_key, 20);
	crypto_hmac_update(rdp->fips_hmac, data, length);
	crypto_hmac_update(rdp->fips_hmac, use_count_le, 4);
	crypto_hmac_final(rdp->fips_hmac, buf, 20);

	memmove(output, buf, 8);
}
