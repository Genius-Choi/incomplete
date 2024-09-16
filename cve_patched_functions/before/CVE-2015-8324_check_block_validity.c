static int check_block_validity(struct inode *inode, const char *msg,
				sector_t logical, sector_t phys, int len)
{
	if (!ext4_data_block_valid(EXT4_SB(inode->i_sb), phys, len)) {
		__ext4_error(inode->i_sb, msg,
			   "inode #%lu logical block %llu mapped to %llu "
			   "(size %d)", inode->i_ino,
			   (unsigned long long) logical,
			   (unsigned long long) phys, len);
		return -EIO;
	}
	return 0;
}
