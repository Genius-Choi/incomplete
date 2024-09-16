static __le32 ext4_superblock_csum(struct super_block *sb,
				   struct ext4_super_block *es)
{
	struct ext4_sb_info *sbi = EXT4_SB(sb);
	int offset = offsetof(struct ext4_super_block, s_checksum);
	__u32 csum;

	csum = ext4_chksum(sbi, ~0, (char *)es, offset);

	return cpu_to_le32(csum);
}
