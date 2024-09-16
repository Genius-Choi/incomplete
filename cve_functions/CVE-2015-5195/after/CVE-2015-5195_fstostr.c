char * fstostr(
	time_t	ntp_stamp
	)
{
	char	*	buf;
	struct tm *	tm;
	time_t		unix_stamp;

	LIB_GETBUF(buf);
	unix_stamp = ntp_stamp - JAN_1970;
	tm = gmtime(&unix_stamp);
	if (NULL == tm)
#ifdef WAIT_FOR_NTP_CRYPTO_C_CALLERS_ABLE_TO_HANDLE_MORE_THAN_20_CHARS
		msnprintf(buf, LIB_BUFLENGTH, "gmtime: %m");
#else
		strncpy(buf, "gmtime() error", LIB_BUFLENGTH);
#endif
	else
		snprintf(buf, LIB_BUFLENGTH, "%04d%02d%02d%02d%02d",
			 tm->tm_year + 1900, tm->tm_mon + 1,
			 tm->tm_mday, tm->tm_hour, tm->tm_min);

	return buf;
}
