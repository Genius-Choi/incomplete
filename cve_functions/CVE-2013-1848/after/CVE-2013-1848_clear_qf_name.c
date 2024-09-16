static int clear_qf_name(struct super_block *sb, int qtype) {

	struct ext3_sb_info *sbi = EXT3_SB(sb);

	if (sb_any_quota_loaded(sb) &&
		sbi->s_qf_names[qtype]) {
		ext3_msg(sb, KERN_ERR, "Cannot change journaled quota options"
			" when quota turned on");
		return 0;
	}
	if (sbi->s_qf_names[qtype]) {
		kfree(sbi->s_qf_names[qtype]);
		sbi->s_qf_names[qtype] = NULL;
	}
	return 1;
}
