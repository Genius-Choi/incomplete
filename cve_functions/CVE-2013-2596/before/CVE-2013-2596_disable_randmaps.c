static int __init disable_randmaps(char *s)
{
	randomize_va_space = 0;
	return 1;
}
