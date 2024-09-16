vrrp_garp_interval_handler(vector_t *strvec)
{
	double interval;

	if (!read_double_strvec(strvec, 1, &interval, 1.0 / TIMER_HZ, UINT_MAX / TIMER_HZ, true))
		report_config_error(CONFIG_GENERAL_ERROR, "vrrp_garp_interval '%s' is invalid", FMT_STR_VSLOT(strvec, 1));
	else
		global_data->vrrp_garp_interval = (unsigned)(interval * TIMER_HZ);

	if (global_data->vrrp_garp_interval >= 1 * TIMER_HZ)
		log_message(LOG_INFO, "The vrrp_garp_interval is very large - %s seconds", FMT_STR_VSLOT(strvec, 1));
}
