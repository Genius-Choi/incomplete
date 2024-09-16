flush_log_file(void)
{
	if (log_file)
		fflush(log_file);
}
