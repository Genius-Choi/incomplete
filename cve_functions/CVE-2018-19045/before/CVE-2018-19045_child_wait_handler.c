child_wait_handler(vector_t *strvec)
{
	unsigned secs;

	if (!strvec)
		return;

	if (!read_unsigned_strvec(strvec, 1, &secs, 0, UINT_MAX, false)) {
		report_config_error(CONFIG_GENERAL_ERROR, "Invalid child_wait_time %s", FMT_STR_VSLOT(strvec, 1));
		return;
	}

	child_wait_time = secs;
}
