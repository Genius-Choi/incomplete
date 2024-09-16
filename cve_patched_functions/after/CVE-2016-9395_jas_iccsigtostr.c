static char *jas_iccsigtostr(int sig, char *buf)
{
	int n;
	int c;
	char *bufptr;
	bufptr = buf;
	for (n = 4; n > 0; --n) {
		c = (sig >> 24) & 0xff;
		if (isalpha(c) || isdigit(c)) {
			*bufptr++ = c;
		}
		sig <<= 8;
	}
	*bufptr = '\0';
	return buf;
}
