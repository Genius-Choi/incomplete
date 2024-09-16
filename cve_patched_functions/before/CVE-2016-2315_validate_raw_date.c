static int validate_raw_date(const char *src, struct strbuf *result)
{
	const char *orig_src = src;
	char *endp;
	unsigned long num;

	errno = 0;

	num = strtoul(src, &endp, 10);
	/* NEEDSWORK: perhaps check for reasonable values? */
	if (errno || endp == src || *endp != ' ')
		return -1;

	src = endp + 1;
	if (*src != '-' && *src != '+')
		return -1;

	num = strtoul(src + 1, &endp, 10);
	if (errno || endp == src + 1 || *endp || 1400 < num)
		return -1;

	strbuf_addstr(result, orig_src);
	return 0;
}
