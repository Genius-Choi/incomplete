static inline int blkcipher_next_copy(struct blkcipher_walk *walk)
{
	u8 *tmp = walk->page;

	blkcipher_map_src(walk);
	memcpy(tmp, walk->src.virt.addr, walk->nbytes);
	blkcipher_unmap_src(walk);

	walk->src.virt.addr = tmp;
	walk->dst.virt.addr = tmp;

	return 0;
}
