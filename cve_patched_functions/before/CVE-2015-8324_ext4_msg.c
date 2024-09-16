void ext4_msg (struct super_block * sb, const char *prefix,
		   const char *fmt, ...)
{
	va_list args;

	va_start(args, fmt);
	printk("%sEXT4-fs (%s): ", prefix, sb->s_id);
	vprintk(fmt, args);
	printk("\n");
	va_end(args);
}
