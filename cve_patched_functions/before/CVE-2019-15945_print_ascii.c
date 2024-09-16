static void print_ascii(const u8 * buf, size_t buflen)
{
	for (; 0 < buflen; buflen--, buf++) {
		if (isprint(*buf))
			printf("%c", *buf);
		else
			putchar('.');
	}
}
