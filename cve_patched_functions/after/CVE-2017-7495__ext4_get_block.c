static int _ext4_get_block(struct inode *inode, sector_t iblock,
			   struct buffer_head *bh, int flags)
{
	struct ext4_map_blocks map;
	int ret = 0;

	if (ext4_has_inline_data(inode))
		return -ERANGE;

	map.m_lblk = iblock;
	map.m_len = bh->b_size >> inode->i_blkbits;

	ret = ext4_map_blocks(ext4_journal_current_handle(), inode, &map,
			      flags);
	if (ret > 0) {
		map_bh(bh, inode->i_sb, map.m_pblk);
		ext4_update_bh_state(bh, map.m_flags);
		bh->b_size = inode->i_sb->s_blocksize * map.m_len;
		ret = 0;
	}
	return ret;
}
