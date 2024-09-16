int createdir(const char *szDirName, int secattr)
{
	int ret = 0;
#ifdef WIN32
	ret = _mkdir(szDirName);
#else
	ret = mkdir(szDirName, secattr);
#endif
	return ret;
}
