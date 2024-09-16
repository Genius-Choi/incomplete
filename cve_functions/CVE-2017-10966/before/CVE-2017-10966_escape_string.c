char *escape_string(const char *str)
{
	char *ret, *p;

	p = ret = g_malloc(strlen(str)*2+1);
	while (*str != '\0') {
		if (*str == '"' || *str == '\'' || *str == '\\')
			*p++ = '\\';
		*p++ = *str++;
	}
	*p = '\0';

	return ret;
}
