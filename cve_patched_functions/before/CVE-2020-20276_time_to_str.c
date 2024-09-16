static char *time_to_str(time_t mtime)
{
	struct tm *t = localtime(&mtime);
	static char str[20];

	setlocale(LC_TIME, "C");
	strftime(str, sizeof(str), "%b %e %H:%M", t);

	return str;
}
