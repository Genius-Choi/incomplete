static int parse_time_interval_uint(const char *time, guint *msecs)
{
	const char *desc;
	guint number;
	int len, ret, digits;

	*msecs = 0;

	/* max. return value is around 24 days */
	number = 0; ret = TRUE; digits = FALSE;
	while (i_isspace(*time))
		time++;
	for (;;) {
		if (i_isdigit(*time)) {
			char *endptr;
			if (!parse_uint(time, &endptr, 10, &number)) {
				return FALSE;
			}
			time = endptr;
			digits = TRUE;
			continue;
		}

		if (!digits)
			return FALSE;

		/* skip punctuation */
		while (*time != '\0' && i_ispunct(*time) && *time != '-')
			time++;

		/* get description */
		for (len = 0, desc = time; i_isalpha(*time); time++)
			len++;

		while (i_isspace(*time))
			time++;

		if (len == 0) {
			if (*time != '\0')
				return FALSE;
			*msecs += number * 1000; /* assume seconds */
			return TRUE;
		}

		if (g_ascii_strncasecmp(desc, "days", len) == 0) {
			if (number > 24) {
				/* would overflow */
				return FALSE;
			}
			*msecs += number * 1000*3600*24;
		} else if (g_ascii_strncasecmp(desc, "hours", len) == 0)
			*msecs += number * 1000*3600;
		else if (g_ascii_strncasecmp(desc, "minutes", len) == 0 ||
			 g_ascii_strncasecmp(desc, "mins", len) == 0)
			*msecs += number * 1000*60;
		else if (g_ascii_strncasecmp(desc, "seconds", len) == 0 ||
			 g_ascii_strncasecmp(desc, "secs", len) == 0)
			*msecs += number * 1000;
		else if (g_ascii_strncasecmp(desc, "milliseconds", len) == 0 ||
			 g_ascii_strncasecmp(desc, "millisecs", len) == 0 ||
			 g_ascii_strncasecmp(desc, "mseconds", len) == 0 ||
			 g_ascii_strncasecmp(desc, "msecs", len) == 0)
			*msecs += number;
		else {
			ret = FALSE;
		}

		/* skip punctuation */
		while (*time != '\0' && i_ispunct(*time) && *time != '-')
			time++;

		if (*time == '\0')
			break;

		number = 0;
		digits = FALSE;
	}

	return ret;
}
