static void validate_coredump_safety(void)
{
#ifdef CONFIG_COREDUMP
	if (suid_dumpable == SUID_DUMP_ROOT &&
	    core_pattern[0] != '/' && core_pattern[0] != '|') {
		printk(KERN_WARNING "Unsafe core_pattern used with "\
			"suid_dumpable=2. Pipe handler or fully qualified "\
			"core dump path required.\n");
	}
#endif
}
