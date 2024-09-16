dynamic_interfaces_handler(vector_t *strvec)
{
	char *str;

	global_data->dynamic_interfaces = true;

	if (vector_size(strvec) >= 2) {
		str = strvec_slot(strvec, 1);

		if (!strcmp(str, "allow_if_changes"))
			global_data->allow_if_changes = true;
		else
			report_config_error(CONFIG_GENERAL_ERROR, "Unknown dynamic_interfaces option '%s'",str);
	}
}
