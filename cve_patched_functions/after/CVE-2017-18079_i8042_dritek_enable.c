static void i8042_dritek_enable(void)
{
	unsigned char param = 0x90;
	int error;

	error = i8042_command(&param, 0x1059);
	if (error)
		pr_warn("Failed to enable DRITEK extension: %d\n", error);
}
