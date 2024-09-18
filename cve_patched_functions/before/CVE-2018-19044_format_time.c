format_time(void)
{
	static char time_buf[TIME_STR_LEN+1];

	strftime(time_buf, sizeof time_buf, "%T ", localtime(&time_now.tv_sec));

	return time_buf;
}
