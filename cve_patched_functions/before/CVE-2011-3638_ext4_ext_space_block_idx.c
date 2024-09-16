static inline int ext4_ext_space_block_idx(struct inode *inode, int check)
{
	int size;

	size = (inode->i_sb->s_blocksize - sizeof(struct ext4_extent_header))
			/ sizeof(struct ext4_extent_idx);
	if (!check) {
#ifdef AGGRESSIVE_TEST
		if (size > 5)
			size = 5;
#endif
	}
	return size;
}
