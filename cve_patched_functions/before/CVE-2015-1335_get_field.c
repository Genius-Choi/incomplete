static char *get_field(char *src, int nfields)
{
	char *p = src;
	int i;

	for (i = 0; i < nfields; i++) {
		while (*p && *p != ' ' && *p != '\t')
			p++;
		if (!*p)
			break;
		p++;
	}
	return p;
}
