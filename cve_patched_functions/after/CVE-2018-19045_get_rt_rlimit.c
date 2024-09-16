get_rt_rlimit(vector_t *strvec, const char *process)
{
	unsigned limit;
	rlim_t rlim;

	if (!read_unsigned_strvec(strvec, 1, &limit, 1, UINT32_MAX, true)) {
		report_config_error(CONFIG_GENERAL_ERROR, "Invalid %s real-time limit - %s", process, FMT_STR_VSLOT(strvec, 1));
		return 0;
	}

	rlim = limit;
	return rlim;
}
