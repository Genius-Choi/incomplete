smtp_alert_vrrp_handler(vector_t *strvec)
{
	int res = true;

	if (vector_size(strvec) >= 2) {
		res = check_true_false(strvec_slot(strvec,1));
		if (res < 0) {
			report_config_error(CONFIG_GENERAL_ERROR, "Invalid value '%s' for global smtp_alert_vrrp specified", FMT_STR_VSLOT(strvec, 1));
			return;
		}
	}

	global_data->smtp_alert_vrrp = res;
}
