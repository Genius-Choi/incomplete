fd_printf (int fd, const char *format, ...)
{
	char buf[256];
	va_list args;
	int len;
	
	va_start(args, format);
	len = vsnprintf(buf, sizeof(buf), format, args);
	buf[sizeof(buf) - 1] = '\0';
	va_end(args);
	
	return writen_ni(fd, buf, len);
}
