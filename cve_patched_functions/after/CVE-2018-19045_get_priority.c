get_priority(vector_t *strvec, const char *process)
{
	int priority;

	if (vector_size(strvec) < 2) {
		report_config_error(CONFIG_GENERAL_ERROR, "No %s process priority specified", process);
		return 0;
	}

	if (!read_int_strvec(strvec, 1, &priority, -20, 19, true)) {
		report_config_error(CONFIG_GENERAL_ERROR, "Invalid %s process priority specified", process);
		return 0;
	}

	return (int8_t)priority;
}
