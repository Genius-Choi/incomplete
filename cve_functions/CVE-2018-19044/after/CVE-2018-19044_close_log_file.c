close_log_file(void)
{
	if (log_file) {
		fclose(log_file);
		log_file = NULL;
	}
}
