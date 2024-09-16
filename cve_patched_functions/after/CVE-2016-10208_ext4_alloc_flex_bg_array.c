int ext4_alloc_flex_bg_array(struct super_block *sb, ext4_group_t ngroup)
{
	struct ext4_sb_info *sbi = EXT4_SB(sb);
	struct flex_groups *new_groups;
	int size;

	if (!sbi->s_log_groups_per_flex)
		return 0;

	size = ext4_flex_group(sbi, ngroup - 1) + 1;
	if (size <= sbi->s_flex_groups_allocated)
		return 0;

	size = roundup_pow_of_two(size * sizeof(struct flex_groups));
	new_groups = ext4_kvzalloc(size, GFP_KERNEL);
	if (!new_groups) {
		ext4_msg(sb, KERN_ERR, "not enough memory for %d flex groups",
			 size / (int) sizeof(struct flex_groups));
		return -ENOMEM;
	}

	if (sbi->s_flex_groups) {
		memcpy(new_groups, sbi->s_flex_groups,
		       (sbi->s_flex_groups_allocated *
			sizeof(struct flex_groups)));
		kvfree(sbi->s_flex_groups);
	}
	sbi->s_flex_groups = new_groups;
	sbi->s_flex_groups_allocated = size / sizeof(struct flex_groups);
	return 0;
}
