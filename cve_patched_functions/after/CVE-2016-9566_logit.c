void logit(int data_type, int display, const char *fmt, ...) {
	va_list ap;
	char *buffer = NULL;

	va_start(ap, fmt);
	if(vasprintf(&buffer, fmt, ap) > 0) {
		write_to_logs_and_console(buffer, data_type, display);
		free(buffer);
		}
	va_end(ap);
	}
