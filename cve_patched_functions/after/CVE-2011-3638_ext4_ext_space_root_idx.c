static inline int ext4_ext_space_root_idx(struct inode *inode, int check)
{
	int size;

	size = sizeof(EXT4_I(inode)->i_data);
	size -= sizeof(struct ext4_extent_header);
	size /= sizeof(struct ext4_extent_idx);
	if (!check) {
#ifdef AGGRESSIVE_TEST
		if (size > 4)
			size = 4;
#endif
	}
	return size;
}
