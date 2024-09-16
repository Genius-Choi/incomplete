BOOL security_encrypt(BYTE* data, int length, rdpRdp* rdp)
{
	if (rdp->encrypt_use_count >= 4096)
	{
		security_key_update(rdp->encrypt_key, rdp->encrypt_update_key, rdp->rc4_key_len);
		crypto_rc4_free(rdp->rc4_encrypt_key);
		rdp->rc4_encrypt_key = crypto_rc4_init(rdp->encrypt_key, rdp->rc4_key_len);
		rdp->encrypt_use_count = 0;
	}
	crypto_rc4(rdp->rc4_encrypt_key, length, data, data);
	rdp->encrypt_use_count++;
	rdp->encrypt_checksum_use_count++;
	return TRUE;
}
