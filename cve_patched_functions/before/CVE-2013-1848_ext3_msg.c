void ext3_msg(struct super_block *sb, const char *prefix,
		const char *fmt, ...)
{
	struct va_format vaf;
	va_list args;

	va_start(args, fmt);

	vaf.fmt = fmt;
	vaf.va = &args;

	printk("%sEXT3-fs (%s): %pV\n", prefix, sb->s_id, &vaf);

	va_end(args);
}
