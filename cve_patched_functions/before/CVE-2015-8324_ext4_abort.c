void ext4_abort(struct super_block *sb, const char *function,
		const char *fmt, ...)
{
	va_list args;

	va_start(args, fmt);
	printk(KERN_CRIT "EXT4-fs error (device %s): %s: ", sb->s_id, function);
	vprintk(fmt, args);
	printk("\n");
	va_end(args);

	if (test_opt(sb, ERRORS_PANIC))
		panic("EXT4-fs panic from previous error\n");

	if (sb->s_flags & MS_RDONLY)
		return;

	ext4_msg(sb, KERN_CRIT, "Remounting filesystem read-only");
	EXT4_SB(sb)->s_mount_state |= EXT4_ERROR_FS;
	sb->s_flags |= MS_RDONLY;
	EXT4_SB(sb)->s_mount_flags |= EXT4_MF_FS_ABORTED;
	if (EXT4_SB(sb)->s_journal)
		jbd2_journal_abort(EXT4_SB(sb)->s_journal, -EIO);
}
