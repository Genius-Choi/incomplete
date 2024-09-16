memcheck_log(const char *called_func, const char *param, const char *file, const char *function, int line)
{
	int len = strlen(called_func) + (param ? strlen(param) : 0);

	if ((len = 36 - len) < 0)
		len = 0;

	fprintf(log_op, "%s%*s%s(%s) at %s, %d, %s\n",
	       format_time(), len, "", called_func, param ? param : "", file, line, function);
}
