int __init reboot_setup(char *str)
{
	reboot_mode = str[0];
	return 1;
}
