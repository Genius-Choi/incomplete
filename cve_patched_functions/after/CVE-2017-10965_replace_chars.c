char *replace_chars(char *str, char from, char to)
{
	char *p;

	for (p = str; *p != '\0'; p++) {
		if (*p == from) *p = to;
	}
	return str;
}
