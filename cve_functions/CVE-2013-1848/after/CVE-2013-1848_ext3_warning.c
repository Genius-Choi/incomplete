void ext3_warning(struct super_block *sb, const char *function,
		  const char *fmt, ...)
{
	struct va_format vaf;
	va_list args;

	va_start(args, fmt);

	vaf.fmt = fmt;
	vaf.va = &args;

	printk(KERN_WARNING "EXT3-fs (%s): warning: %s: %pV\n",
	       sb->s_id, function, &vaf);

	va_end(args);
}
