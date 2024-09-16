dlopen(const char *dll_name, int flags)
{
	wchar_t wbuf[W_PATH_MAX];
	(void)flags;
	path_to_unicode(NULL, dll_name, wbuf, ARRAY_SIZE(wbuf));
	return LoadLibraryW(wbuf);
}
