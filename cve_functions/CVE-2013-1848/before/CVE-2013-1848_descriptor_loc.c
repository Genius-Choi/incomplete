static ext3_fsblk_t descriptor_loc(struct super_block *sb,
				    ext3_fsblk_t logic_sb_block,
				    int nr)
{
	struct ext3_sb_info *sbi = EXT3_SB(sb);
	unsigned long bg, first_meta_bg;
	int has_super = 0;

	first_meta_bg = le32_to_cpu(sbi->s_es->s_first_meta_bg);

	if (!EXT3_HAS_INCOMPAT_FEATURE(sb, EXT3_FEATURE_INCOMPAT_META_BG) ||
	    nr < first_meta_bg)
		return (logic_sb_block + nr + 1);
	bg = sbi->s_desc_per_block * nr;
	if (ext3_bg_has_super(sb, bg))
		has_super = 1;
	return (has_super + ext3_group_first_block_no(sb, bg));
}
