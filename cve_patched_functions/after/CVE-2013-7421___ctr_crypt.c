static unsigned int __ctr_crypt(struct blkcipher_desc *desc,
				struct blkcipher_walk *walk)
{
	struct des3_ede_x86_ctx *ctx = crypto_blkcipher_ctx(desc->tfm);
	unsigned int bsize = DES3_EDE_BLOCK_SIZE;
	unsigned int nbytes = walk->nbytes;
	__be64 *src = (__be64 *)walk->src.virt.addr;
	__be64 *dst = (__be64 *)walk->dst.virt.addr;
	u64 ctrblk = be64_to_cpu(*(__be64 *)walk->iv);
	__be64 ctrblocks[3];

	/* Process four block batch */
	if (nbytes >= bsize * 3) {
		do {
			/* create ctrblks for parallel encrypt */
			ctrblocks[0] = cpu_to_be64(ctrblk++);
			ctrblocks[1] = cpu_to_be64(ctrblk++);
			ctrblocks[2] = cpu_to_be64(ctrblk++);

			des3_ede_enc_blk_3way(ctx, (u8 *)ctrblocks,
					      (u8 *)ctrblocks);

			dst[0] = src[0] ^ ctrblocks[0];
			dst[1] = src[1] ^ ctrblocks[1];
			dst[2] = src[2] ^ ctrblocks[2];

			src += 3;
			dst += 3;
		} while ((nbytes -= bsize * 3) >= bsize * 3);

		if (nbytes < bsize)
			goto done;
	}

	/* Handle leftovers */
	do {
		ctrblocks[0] = cpu_to_be64(ctrblk++);

		des3_ede_enc_blk(ctx, (u8 *)ctrblocks, (u8 *)ctrblocks);

		dst[0] = src[0] ^ ctrblocks[0];

		src += 1;
		dst += 1;
	} while ((nbytes -= bsize) >= bsize);

done:
	*(__be64 *)walk->iv = cpu_to_be64(ctrblk);
	return nbytes;
}
