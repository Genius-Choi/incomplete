static int crypto_pcbc_encrypt_inplace(struct blkcipher_desc *desc,
				       struct blkcipher_walk *walk,
				       struct crypto_cipher *tfm)
{
	void (*fn)(struct crypto_tfm *, u8 *, const u8 *) =
		crypto_cipher_alg(tfm)->cia_encrypt;
	int bsize = crypto_cipher_blocksize(tfm);
	unsigned int nbytes = walk->nbytes;
	u8 *src = walk->src.virt.addr;
	u8 *iv = walk->iv;
	u8 tmpbuf[bsize];

	do {
		memcpy(tmpbuf, src, bsize);
		crypto_xor(iv, src, bsize);
		fn(crypto_cipher_tfm(tfm), src, iv);
		memcpy(iv, tmpbuf, bsize);
		crypto_xor(iv, src, bsize);

		src += bsize;
	} while ((nbytes -= bsize) >= bsize);

	memcpy(walk->iv, iv, bsize);

	return nbytes;
}
