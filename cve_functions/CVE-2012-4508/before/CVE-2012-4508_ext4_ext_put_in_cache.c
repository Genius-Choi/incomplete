ext4_ext_put_in_cache(struct inode *inode, ext4_lblk_t block,
			__u32 len, ext4_fsblk_t start)
{
	struct ext4_ext_cache *cex;
	BUG_ON(len == 0);
	spin_lock(&EXT4_I(inode)->i_block_reservation_lock);
	trace_ext4_ext_put_in_cache(inode, block, len, start);
	cex = &EXT4_I(inode)->i_cached_extent;
	cex->ec_block = block;
	cex->ec_len = len;
	cex->ec_start = start;
	spin_unlock(&EXT4_I(inode)->i_block_reservation_lock);
}
