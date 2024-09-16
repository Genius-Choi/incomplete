static int ext4_inode_csum_verify(struct inode *inode, struct ext4_inode *raw,
				  struct ext4_inode_info *ei)
{
	__u32 provided, calculated;

	if (EXT4_SB(inode->i_sb)->s_es->s_creator_os !=
	    cpu_to_le32(EXT4_OS_LINUX) ||
	    !ext4_has_metadata_csum(inode->i_sb))
		return 1;

	provided = le16_to_cpu(raw->i_checksum_lo);
	calculated = ext4_inode_csum(inode, raw, ei);
	if (EXT4_INODE_SIZE(inode->i_sb) > EXT4_GOOD_OLD_INODE_SIZE &&
	    EXT4_FITS_IN_INODE(raw, ei, i_checksum_hi))
		provided |= ((__u32)le16_to_cpu(raw->i_checksum_hi)) << 16;
	else
		calculated &= 0xFFFF;

	return provided == calculated;
}
