PGTYPESdate_to_asc(date dDate)
{
	struct tm	tt,
			   *tm = &tt;
	char		buf[MAXDATELEN + 1];
	int			DateStyle = 1;
	bool		EuroDates = FALSE;

	j2date(dDate + date2j(2000, 1, 1), &(tm->tm_year), &(tm->tm_mon), &(tm->tm_mday));
	EncodeDateOnly(tm, DateStyle, buf, EuroDates);
	return pgtypes_strdup(buf);
}
