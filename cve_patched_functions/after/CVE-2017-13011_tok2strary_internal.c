tok2strary_internal(register const char **lp, int n, register const char *fmt,
	register int v)
{
	static char buf[TOKBUFSIZE];

	if (v >= 0 && v < n && lp[v] != NULL)
		return lp[v];
	if (fmt == NULL)
		fmt = "#%d";
	(void)snprintf(buf, sizeof(buf), fmt, v);
	return (buf);
}
