static int skcipher_walk_next(struct skcipher_walk *walk)
{
	unsigned int bsize;
	unsigned int n;
	int err;

	walk->flags &= ~(SKCIPHER_WALK_SLOW | SKCIPHER_WALK_COPY |
			 SKCIPHER_WALK_DIFF);

	n = walk->total;
	bsize = min(walk->stride, max(n, walk->blocksize));
	n = scatterwalk_clamp(&walk->in, n);
	n = scatterwalk_clamp(&walk->out, n);

	if (unlikely(n < bsize)) {
		if (unlikely(walk->total < walk->blocksize))
			return skcipher_walk_done(walk, -EINVAL);

slow_path:
		err = skcipher_next_slow(walk, bsize);
		goto set_phys_lowmem;
	}

	if (unlikely((walk->in.offset | walk->out.offset) & walk->alignmask)) {
		if (!walk->page) {
			gfp_t gfp = skcipher_walk_gfp(walk);

			walk->page = (void *)__get_free_page(gfp);
			if (!walk->page)
				goto slow_path;
		}

		walk->nbytes = min_t(unsigned, n,
				     PAGE_SIZE - offset_in_page(walk->page));
		walk->flags |= SKCIPHER_WALK_COPY;
		err = skcipher_next_copy(walk);
		goto set_phys_lowmem;
	}

	walk->nbytes = n;

	return skcipher_next_fast(walk);

set_phys_lowmem:
	if (!err && (walk->flags & SKCIPHER_WALK_PHYS)) {
		walk->src.phys.page = virt_to_page(walk->src.virt.addr);
		walk->dst.phys.page = virt_to_page(walk->dst.virt.addr);
		walk->src.phys.offset &= PAGE_SIZE - 1;
		walk->dst.phys.offset &= PAGE_SIZE - 1;
	}
	return err;
}
