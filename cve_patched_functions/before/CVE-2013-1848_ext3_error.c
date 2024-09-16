void ext3_error(struct super_block *sb, const char *function,
		const char *fmt, ...)
{
	struct va_format vaf;
	va_list args;

	va_start(args, fmt);

	vaf.fmt = fmt;
	vaf.va = &args;

	printk(KERN_CRIT "EXT3-fs error (device %s): %s: %pV\n",
	       sb->s_id, function, &vaf);

	va_end(args);

	ext3_handle_error(sb);
}
