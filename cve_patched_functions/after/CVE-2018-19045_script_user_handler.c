script_user_handler(vector_t *strvec)
{
	if (vector_size(strvec) < 2) {
		report_config_error(CONFIG_GENERAL_ERROR, "No script username specified");
		return;
	}

	if (set_default_script_user(strvec_slot(strvec, 1), vector_size(strvec) > 2 ? strvec_slot(strvec, 2) : NULL))
		report_config_error(CONFIG_GENERAL_ERROR, "Error setting global script uid/gid");
}
