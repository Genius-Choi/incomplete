IW_IMPL(int) iw_stricmp(const char *s1, const char *s2)
{
#ifdef IW_WINDOWS
	return _stricmp(s1,s2);
#else
	return strcasecmp(s1,s2);
#endif
}
