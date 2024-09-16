int close_log_file(void)
{
	if(!log_fp)
		return 0;

	fflush(log_fp);
	fclose(log_fp);
	log_fp = NULL;
	return 0;
}
