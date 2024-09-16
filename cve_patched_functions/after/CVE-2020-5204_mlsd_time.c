static char *mlsd_time(time_t mtime)
{
	struct tm *t = localtime(&mtime);
	static char str[20];

	strftime(str, sizeof(str), "%Y%m%d%H%M%S", t);

	return str;
}
