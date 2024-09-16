void ext3_abort(struct super_block *sb, const char *function,
		 const char *fmt, ...)
{
	struct va_format vaf;
	va_list args;

	va_start(args, fmt);

	vaf.fmt = fmt;
	vaf.va = &args;

	printk(KERN_CRIT "EXT3-fs (%s): error: %s: %pV\n",
	       sb->s_id, function, &vaf);

	va_end(args);

	if (test_opt(sb, ERRORS_PANIC))
		panic("EXT3-fs: panic from previous error\n");

	if (sb->s_flags & MS_RDONLY)
		return;

	ext3_msg(sb, KERN_CRIT,
		"error: remounting filesystem read-only");
	EXT3_SB(sb)->s_mount_state |= EXT3_ERROR_FS;
	sb->s_flags |= MS_RDONLY;
	set_opt(EXT3_SB(sb)->s_mount_opt, ABORT);
	if (EXT3_SB(sb)->s_journal)
		journal_abort(EXT3_SB(sb)->s_journal, -EIO);
}
