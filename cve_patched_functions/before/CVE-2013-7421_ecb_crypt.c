static int ecb_crypt(struct blkcipher_desc *desc, struct blkcipher_walk *walk,
		     const u32 *expkey)
{
	unsigned int bsize = DES3_EDE_BLOCK_SIZE;
	unsigned int nbytes;
	int err;

	err = blkcipher_walk_virt(desc, walk);

	while ((nbytes = walk->nbytes)) {
		u8 *wsrc = walk->src.virt.addr;
		u8 *wdst = walk->dst.virt.addr;

		/* Process four block batch */
		if (nbytes >= bsize * 3) {
			do {
				des3_ede_x86_64_crypt_blk_3way(expkey, wdst,
							       wsrc);

				wsrc += bsize * 3;
				wdst += bsize * 3;
				nbytes -= bsize * 3;
			} while (nbytes >= bsize * 3);

			if (nbytes < bsize)
				goto done;
		}

		/* Handle leftovers */
		do {
			des3_ede_x86_64_crypt_blk(expkey, wdst, wsrc);

			wsrc += bsize;
			wdst += bsize;
			nbytes -= bsize;
		} while (nbytes >= bsize);

done:
		err = blkcipher_walk_done(desc, walk, nbytes);
	}

	return err;
}
