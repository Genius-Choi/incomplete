static int ext4_verify_csum_type(struct super_block *sb,
				 struct ext4_super_block *es)
{
	if (!ext4_has_feature_metadata_csum(sb))
		return 1;

	return es->s_checksum_type == EXT4_CRC32C_CHKSUM;
}
