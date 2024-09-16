char *ascii_strup(char *str)
{
	char *s;

	for (s = str; *s; s++)
		*s = g_ascii_toupper (*s);
	return str;
}
