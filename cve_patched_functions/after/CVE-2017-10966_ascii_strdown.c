char *ascii_strdown(char *str)
{
	char *s;

	for (s = str; *s; s++)
		*s = g_ascii_tolower (*s);
	return str;
}
