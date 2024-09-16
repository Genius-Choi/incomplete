goodchar(unsigned char x, const char *extra)
{
	return (isascii(x) && isalnum(x)) || strchr(extra, x);
}
