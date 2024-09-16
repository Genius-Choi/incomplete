void gfs2_trim_blocks(struct inode *inode)
{
	u64 size = inode->i_size;
	int ret;

	ret = do_shrink(inode, size, size);
	WARN_ON(ret != 0);
}
