int gfs2_extent_map(struct inode *inode, u64 lblock, int *new, u64 *dblock, unsigned *extlen)
{
	struct buffer_head bh = { .b_state = 0, .b_blocknr = 0 };
	int ret;
	int create = *new;

	BUG_ON(!extlen);
	BUG_ON(!dblock);
	BUG_ON(!new);

	bh.b_size = 1 << (inode->i_blkbits + (create ? 0 : 5));
	ret = gfs2_block_map(inode, lblock, &bh, create);
	*extlen = bh.b_size >> inode->i_blkbits;
	*dblock = bh.b_blocknr;
	if (buffer_new(&bh))
		*new = 1;
	else
		*new = 0;
	return ret;
}
