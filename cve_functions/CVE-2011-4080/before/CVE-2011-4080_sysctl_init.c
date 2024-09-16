static __init int sysctl_init(void)
{
	sysctl_set_parent(NULL, root_table);
#ifdef CONFIG_SYSCTL_SYSCALL_CHECK
	sysctl_check_table(current->nsproxy, root_table);
#endif
	return 0;
}
