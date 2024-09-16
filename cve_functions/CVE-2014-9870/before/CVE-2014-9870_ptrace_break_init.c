static int __init ptrace_break_init(void)
{
	register_undef_hook(&arm_break_hook);
	register_undef_hook(&thumb_break_hook);
	register_undef_hook(&thumb2_break_hook);
	return 0;
}
