static void ext3_handle_error(struct super_block *sb)
{
	struct ext3_super_block *es = EXT3_SB(sb)->s_es;

	EXT3_SB(sb)->s_mount_state |= EXT3_ERROR_FS;
	es->s_state |= cpu_to_le16(EXT3_ERROR_FS);

	if (sb->s_flags & MS_RDONLY)
		return;

	if (!test_opt (sb, ERRORS_CONT)) {
		journal_t *journal = EXT3_SB(sb)->s_journal;

		set_opt(EXT3_SB(sb)->s_mount_opt, ABORT);
		if (journal)
			journal_abort(journal, -EIO);
	}
	if (test_opt (sb, ERRORS_RO)) {
		ext3_msg(sb, KERN_CRIT,
			"error: remounting filesystem read-only");
		sb->s_flags |= MS_RDONLY;
	}
	ext3_commit_super(sb, es, 1);
	if (test_opt(sb, ERRORS_PANIC))
		panic("EXT3-fs (%s): panic forced after error\n",
			sb->s_id);
}
