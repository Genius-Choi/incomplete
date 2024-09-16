static int __init init_sysctl(void)
{
	sysctl_header = register_sysctl_table(sh64_root);
	return 0;
}
