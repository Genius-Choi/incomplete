void progressbar_info(char *fmt, ...)
{
	va_list ap;

	pthread_mutex_lock(&screen_mutex);

	if(progress_enabled)
		printf("\n");

	va_start(ap, fmt);
	vprintf(fmt, ap);
	va_end(ap);

	pthread_mutex_unlock(&screen_mutex);
}
