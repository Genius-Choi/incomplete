static int __init fault_around_debugfs(void)
{
	void *ret;

	ret = debugfs_create_file("fault_around_bytes", 0644, NULL, NULL,
			&fault_around_bytes_fops);
	if (!ret)
		pr_warn("Failed to create fault_around_bytes in debugfs");
	return 0;
}
