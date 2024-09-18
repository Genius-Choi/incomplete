static int opensc_info(void)
{
	printf (
		"%s %s ",
		PACKAGE_NAME,
		PACKAGE_VERSION
	);

#if defined(__VERSION__)
	printf (
		"[%s %s]\n",
#if defined(__GNUC__)
		"gcc ",
#else
		"unknown ",
#endif
		__VERSION__
	);
#elif defined(__SUNPRO_C)
	printf (
		"[Sun C %x.%x]\n",
#if __SUNPRO_C > 0x590
		(__SUNPRO_C >> 12), (__SUNPRO_C >> 4) & 0xFF
#else
		(__SUNPRO_C >>  8), (__SUNPRO_C >> 4) & 0xF
#endif
	);
#elif defined(_MSC_VER)
	printf ("[Microsoft %d]\n", _MSC_VER);
#else
	printf ("[Unknown compiler, please report]");
#endif
	printf ("Enabled features:%s\n", OPENSC_FEATURES);
	return 0;
}
