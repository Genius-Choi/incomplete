int mkdir_deep(const char *szDirName, int secattr)
{
	char DirName[260];
	DirName[0] = 0;
	const char* p = szDirName;
	char* q = DirName;
	int ret = 0;
	while(*p)
	{
		if (('\\' == *p) || ('/' == *p))
		{
			if (':' != *(p-1))
			{
				ret = createdir(DirName, secattr);
			}
		}
		*q++ = *p++;
		*q = '\0';
	}
	if (DirName[0])
	{
		ret = createdir(DirName, secattr);
	}
	return ret;
}
