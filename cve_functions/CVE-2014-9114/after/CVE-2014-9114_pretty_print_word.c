static int pretty_print_word(const char *str, int max_len,
			     int left_len, int overflow_nl)
{
	int len = strlen(str) + left_len;
	int ret = 0;

	fputs(str, stdout);
	if (overflow_nl && len > max_len) {
		fputc('\n', stdout);
		len = 0;
	} else if (len > max_len)
		ret = len - max_len;
	do
		fputc(' ', stdout);
	while (len++ < max_len);
	return ret;
}
