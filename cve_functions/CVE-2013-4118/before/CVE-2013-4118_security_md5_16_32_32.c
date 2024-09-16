void security_md5_16_32_32(const BYTE* in0, const BYTE* in1, const BYTE* in2, BYTE* output)
{
	CryptoMd5 md5;

	md5 = crypto_md5_init();
	crypto_md5_update(md5, in0, 16);
	crypto_md5_update(md5, in1, 32);
	crypto_md5_update(md5, in2, 32);
	crypto_md5_final(md5, output);
}
