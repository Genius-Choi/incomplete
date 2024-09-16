void progressbar_error(char *fmt, ...)
{
	va_list ap;

	pthread_mutex_lock(&screen_mutex);

	if(progress_enabled)
		fprintf(stderr, "\n");

	va_start(ap, fmt);
	vfprintf(stderr, fmt, ap);
	va_end(ap);

	pthread_mutex_unlock(&screen_mutex);
}
