static char *find_field(char *nf, char *of)
{
	if (nf)
		return nf;
	if (of)
		return of;
	return xstrdup("");
}
