static struct crypto_skcipher *ceph_crypto_alloc_cipher(void)
{
	return crypto_alloc_skcipher("cbc(aes)", 0, CRYPTO_ALG_ASYNC);
}
