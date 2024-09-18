static int crypto_pcbc_decrypt(struct blkcipher_desc *desc,
			       struct scatterlist *dst, struct scatterlist *src,
			       unsigned int nbytes)
{
	struct blkcipher_walk walk;
	struct crypto_blkcipher *tfm = desc->tfm;
	struct crypto_pcbc_ctx *ctx = crypto_blkcipher_ctx(tfm);
	struct crypto_cipher *child = ctx->child;
	int err;

	blkcipher_walk_init(&walk, dst, src, nbytes);
	err = blkcipher_walk_virt(desc, &walk);

	while ((nbytes = walk.nbytes)) {
		if (walk.src.virt.addr == walk.dst.virt.addr)
			nbytes = crypto_pcbc_decrypt_inplace(desc, &walk,
							     child);
		else
			nbytes = crypto_pcbc_decrypt_segment(desc, &walk,
							     child);
		err = blkcipher_walk_done(desc, &walk, nbytes);
	}

	return err;
}
