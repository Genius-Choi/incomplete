int __init sysctl_init(void)
{
	struct ctl_table_header *hdr;

	hdr = register_sysctl_table(sysctl_base_table);
	kmemleak_not_leak(hdr);
	return 0;
}
