static inline int ext3_feature_set_ok(struct super_block *sb)
{
	if (ext4_has_unknown_ext3_incompat_features(sb))
		return 0;
	if (!ext4_has_feature_journal(sb))
		return 0;
	if (sb->s_flags & MS_RDONLY)
		return 1;
	if (ext4_has_unknown_ext3_ro_compat_features(sb))
		return 0;
	return 1;
}
