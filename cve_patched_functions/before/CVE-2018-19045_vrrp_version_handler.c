vrrp_version_handler(vector_t *strvec)
{
	int version;

	if (!read_int_strvec(strvec, 1, &version, 2, 3, true)) {
		report_config_error(CONFIG_GENERAL_ERROR, "VRRP Error: Version must be either 2 or 3");
		return;
	}

	global_data->vrrp_version = version;
}
