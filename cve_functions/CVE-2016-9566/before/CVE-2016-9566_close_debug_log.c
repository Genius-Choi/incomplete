int close_debug_log(void) {

	if(debug_file_fp != NULL)
		fclose(debug_file_fp);

	debug_file_fp = NULL;

	return OK;
	}
