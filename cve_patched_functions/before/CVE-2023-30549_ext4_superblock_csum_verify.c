static int ext4_superblock_csum_verify(struct super_block *sb,
				       struct ext4_super_block *es)
{
	if (!ext4_has_metadata_csum(sb))
		return 1;

	return es->s_checksum == ext4_superblock_csum(sb, es);
}
