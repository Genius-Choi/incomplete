void ext4_superblock_csum_set(struct super_block *sb)
{
	struct ext4_super_block *es = EXT4_SB(sb)->s_es;

	if (!ext4_has_metadata_csum(sb))
		return;

	es->s_checksum = ext4_superblock_csum(sb, es);
}
