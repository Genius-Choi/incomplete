int blkcipher_walk_done(struct blkcipher_desc *desc,
			struct blkcipher_walk *walk, int err)
{
	struct crypto_blkcipher *tfm = desc->tfm;
	unsigned int nbytes = 0;

	if (likely(err >= 0)) {
		unsigned int n = walk->nbytes - err;

		if (likely(!(walk->flags & BLKCIPHER_WALK_SLOW)))
			n = blkcipher_done_fast(walk, n);
		else if (WARN_ON(err)) {
			err = -EINVAL;
			goto err;
		} else
			n = blkcipher_done_slow(tfm, walk, n);

		nbytes = walk->total - n;
		err = 0;
	}

	scatterwalk_done(&walk->in, 0, nbytes);
	scatterwalk_done(&walk->out, 1, nbytes);

err:
	walk->total = nbytes;
	walk->nbytes = nbytes;

	if (nbytes) {
		crypto_yield(desc->flags);
		return blkcipher_walk_next(desc, walk);
	}

	if (walk->iv != desc->info)
		memcpy(desc->info, walk->iv, crypto_blkcipher_ivsize(tfm));
	if (walk->buffer != walk->page)
		kfree(walk->buffer);
	if (walk->page)
		free_page((unsigned long)walk->page);

	return err;
}
