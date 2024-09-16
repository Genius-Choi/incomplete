int ext4_get_block_dax(struct inode *inode, sector_t iblock,
		   struct buffer_head *bh_result, int create)
{
	int flags = EXT4_GET_BLOCKS_PRE_IO | EXT4_GET_BLOCKS_UNWRIT_EXT;
	if (create)
		flags |= EXT4_GET_BLOCKS_CREATE;
	ext4_debug("ext4_get_block_dax: inode %lu, create flag %d\n",
		   inode->i_ino, create);
	return _ext4_get_block(inode, iblock, bh_result, flags);
}
