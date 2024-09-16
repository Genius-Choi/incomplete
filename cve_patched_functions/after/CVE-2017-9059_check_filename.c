check_filename(char *str, int len)
{
	int i;

	if (len == 0)
		return nfserr_inval;
	if (isdotent(str, len))
		return nfserr_badname;
	for (i = 0; i < len; i++)
		if (str[i] == '/')
			return nfserr_badname;
	return 0;
}
