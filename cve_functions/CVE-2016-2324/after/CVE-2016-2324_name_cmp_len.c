static int name_cmp_len(const char *name)
{
	int i;
	for (i = 0; name[i] && name[i] != '\n' && name[i] != '/'; i++)
		;
	return i;
}
