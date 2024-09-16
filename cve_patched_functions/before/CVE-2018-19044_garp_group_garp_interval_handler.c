garp_group_garp_interval_handler(vector_t *strvec)
{
	garp_delay_t *delay = LIST_TAIL_DATA(garp_delay);
	double val;

	if (!read_double_strvec(strvec, 1, &val, 0, INT_MAX / 1000000, true)) {
		report_config_error(CONFIG_GENERAL_ERROR, "garp_group garp_interval '%s' invalid", FMT_STR_VSLOT(strvec, 1));
		return;
	}

	delay->garp_interval.tv_sec = (time_t)val;
	delay->garp_interval.tv_usec = (suseconds_t)((val - delay->garp_interval.tv_sec) * 1000000);
	delay->have_garp_interval = true;

	if (delay->garp_interval.tv_sec >= 1)
		log_message(LOG_INFO, "The garp_interval is very large - %s seconds", FMT_STR_VSLOT(strvec,1));
}
