BOOL security_fips_decrypt(BYTE* data, int length, rdpRdp* rdp)
{
	crypto_des3_decrypt(rdp->fips_decrypt, length, data, data);
	return TRUE;
}
