void ndp_log(struct ndp *ndp, int priority,
	     const char *file, int line, const char *fn,
	     const char *format, ...)
{
	va_list args;

	va_start(args, format);
	ndp->log_fn(ndp, priority, file, line, fn, format, args);
	va_end(args);
}
