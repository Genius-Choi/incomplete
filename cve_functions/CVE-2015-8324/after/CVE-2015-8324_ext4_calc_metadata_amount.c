static int ext4_calc_metadata_amount(struct inode *inode, sector_t lblock)
{
	if (EXT4_I(inode)->i_flags & EXT4_EXTENTS_FL)
		return ext4_ext_calc_metadata_amount(inode, lblock);

	return ext4_indirect_calc_metadata_amount(inode, lblock);
}
