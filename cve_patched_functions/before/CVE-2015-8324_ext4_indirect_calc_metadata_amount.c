static int ext4_indirect_calc_metadata_amount(struct inode *inode,
					      sector_t lblock)
{
	struct ext4_inode_info *ei = EXT4_I(inode);
	int dind_mask = EXT4_ADDR_PER_BLOCK(inode->i_sb) - 1;
	int blk_bits;

	if (lblock < EXT4_NDIR_BLOCKS)
		return 0;

	lblock -= EXT4_NDIR_BLOCKS;

	if (ei->i_da_metadata_calc_len &&
	    (lblock & dind_mask) == ei->i_da_metadata_calc_last_lblock) {
		ei->i_da_metadata_calc_len++;
		return 0;
	}
	ei->i_da_metadata_calc_last_lblock = lblock & dind_mask;
	ei->i_da_metadata_calc_len = 1;
	blk_bits = roundup_pow_of_two(lblock + 1);
	return (blk_bits / EXT4_ADDR_PER_BLOCK_BITS(inode->i_sb)) + 1;
}
