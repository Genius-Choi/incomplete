PGTYPESdate_today(date * d)
{
	struct tm	ts;

	GetCurrentDateTime(&ts);
	if (errno == 0)
		*d = date2j(ts.tm_year, ts.tm_mon, ts.tm_mday) - date2j(2000, 1, 1);
	return;
}
