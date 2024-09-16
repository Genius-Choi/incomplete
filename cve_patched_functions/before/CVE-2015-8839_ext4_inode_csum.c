static __u32 ext4_inode_csum(struct inode *inode, struct ext4_inode *raw,
			      struct ext4_inode_info *ei)
{
	struct ext4_sb_info *sbi = EXT4_SB(inode->i_sb);
	__u16 csum_lo;
	__u16 csum_hi = 0;
	__u32 csum;

	csum_lo = le16_to_cpu(raw->i_checksum_lo);
	raw->i_checksum_lo = 0;
	if (EXT4_INODE_SIZE(inode->i_sb) > EXT4_GOOD_OLD_INODE_SIZE &&
	    EXT4_FITS_IN_INODE(raw, ei, i_checksum_hi)) {
		csum_hi = le16_to_cpu(raw->i_checksum_hi);
		raw->i_checksum_hi = 0;
	}

	csum = ext4_chksum(sbi, ei->i_csum_seed, (__u8 *)raw,
			   EXT4_INODE_SIZE(inode->i_sb));

	raw->i_checksum_lo = cpu_to_le16(csum_lo);
	if (EXT4_INODE_SIZE(inode->i_sb) > EXT4_GOOD_OLD_INODE_SIZE &&
	    EXT4_FITS_IN_INODE(raw, ei, i_checksum_hi))
		raw->i_checksum_hi = cpu_to_le16(csum_hi);

	return csum;
}
