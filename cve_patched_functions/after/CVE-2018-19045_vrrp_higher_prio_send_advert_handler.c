vrrp_higher_prio_send_advert_handler(vector_t *strvec)
{
	int res;

	if (vector_size(strvec) >= 2) {
		res = check_true_false(strvec_slot(strvec,1));
		if (res < 0)
			report_config_error(CONFIG_GENERAL_ERROR, "Invalid value for vrrp_higher_prio_send_advert specified");
		else
			global_data->vrrp_higher_prio_send_advert = res;
	}
	else
		global_data->vrrp_higher_prio_send_advert = true;
}
