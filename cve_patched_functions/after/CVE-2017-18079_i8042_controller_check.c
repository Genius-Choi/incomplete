static int i8042_controller_check(void)
{
	if (i8042_flush()) {
		pr_info("No controller found\n");
		return -ENODEV;
	}

	return 0;
}
