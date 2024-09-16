static int ext3_quota_on_mount(struct super_block *sb, int type)
{
	return dquot_quota_on_mount(sb, EXT3_SB(sb)->s_qf_names[type],
					EXT3_SB(sb)->s_jquota_fmt, type);
}
