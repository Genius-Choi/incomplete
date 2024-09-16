static void log_stderr(struct ndp *ndp, int priority,
		       const char *file, int line, const char *fn,
		       const char *format, va_list args)
{
	fprintf(stderr, "libndp: %s: ", fn);
	vfprintf(stderr, format, args);
	fprintf(stderr, "\n");
}
