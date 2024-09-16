vrrp_auth_pass_handler(vector_t *strvec)
{
	vrrp_t *vrrp = LIST_TAIL_DATA(vrrp_data->vrrp);
	char *str = strvec_slot(strvec, 1);
	size_t max_size = sizeof (vrrp->auth_data);
	size_t str_len = strlen(str);

	if (str_len > max_size) {
		str_len = max_size;
		report_config_error(CONFIG_GENERAL_ERROR,
			    "Truncating auth_pass to %zu characters", max_size);
	}

	memset(vrrp->auth_data, 0, max_size);
	memcpy(vrrp->auth_data, str, str_len);
}
