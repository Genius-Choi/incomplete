static int __ext4_ext_check_block(const char *function, unsigned int line,
				  struct inode *inode,
				  struct ext4_extent_header *eh,
				  int depth,
				  struct buffer_head *bh)
{
	int ret;

	if (buffer_verified(bh))
		return 0;
	ret = ext4_ext_check(inode, eh, depth);
	if (ret)
		return ret;
	set_buffer_verified(bh);
	return ret;
}
