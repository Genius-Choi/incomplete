static inline void ext3_show_quota_options(struct seq_file *seq, struct super_block *sb)
{
#if defined(CONFIG_QUOTA)
	struct ext3_sb_info *sbi = EXT3_SB(sb);

	if (sbi->s_jquota_fmt) {
		char *fmtname = "";

		switch (sbi->s_jquota_fmt) {
		case QFMT_VFS_OLD:
			fmtname = "vfsold";
			break;
		case QFMT_VFS_V0:
			fmtname = "vfsv0";
			break;
		case QFMT_VFS_V1:
			fmtname = "vfsv1";
			break;
		}
		seq_printf(seq, ",jqfmt=%s", fmtname);
	}

	if (sbi->s_qf_names[USRQUOTA])
		seq_printf(seq, ",usrjquota=%s", sbi->s_qf_names[USRQUOTA]);

	if (sbi->s_qf_names[GRPQUOTA])
		seq_printf(seq, ",grpjquota=%s", sbi->s_qf_names[GRPQUOTA]);

	if (test_opt(sb, USRQUOTA))
		seq_puts(seq, ",usrquota");

	if (test_opt(sb, GRPQUOTA))
		seq_puts(seq, ",grpquota");
#endif
}
