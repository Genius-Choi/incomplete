char *show_lowascii(const char *str)
{
	char *ret, *p;

	ret = p = g_malloc(strlen(str)*2+1);
	while (*str != '\0') {
		if ((unsigned char) *str >= 32)
			*p++ = *str;
		else {
			*p++ = '^';
			*p++ = *str + 'A'-1;
		}
		str++;
	}
	*p = '\0';

	return ret;
}
