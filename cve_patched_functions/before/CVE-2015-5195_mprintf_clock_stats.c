mprintf_clock_stats(
	sockaddr_u *addr,
	const char *fmt,
	...
	)
{
	va_list	ap;
	int	rc;
	char	msg[512];

	va_start(ap, fmt);
	rc = mvsnprintf(msg, sizeof(msg), fmt, ap);
	va_end(ap);
	if (stats_control)
		record_clock_stats(addr, msg);

	return rc;
}
