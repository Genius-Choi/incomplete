void __ext4_msg(struct super_block *sb,
		const char *prefix, const char *fmt, ...)
{
	struct va_format vaf;
	va_list args;

	if (!___ratelimit(&(EXT4_SB(sb)->s_msg_ratelimit_state), "EXT4-fs"))
		return;

	va_start(args, fmt);
	vaf.fmt = fmt;
	vaf.va = &args;
	printk("%sEXT4-fs (%s): %pV\n", prefix, sb->s_id, &vaf);
	va_end(args);
}
