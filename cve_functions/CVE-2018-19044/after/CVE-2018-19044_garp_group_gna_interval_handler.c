garp_group_gna_interval_handler(vector_t *strvec)
{
	garp_delay_t *delay = LIST_TAIL_DATA(garp_delay);
	double val;

	if (!read_double_strvec(strvec, 1, &val, 0, INT_MAX / 1000000, true)) {
		report_config_error(CONFIG_GENERAL_ERROR, "garp_group gna_interval '%s' invalid", FMT_STR_VSLOT(strvec, 1));
		return;
	}

	delay->gna_interval.tv_sec = (time_t)val;
	delay->gna_interval.tv_usec = (suseconds_t)((val - delay->gna_interval.tv_sec) * 1000000);
	delay->have_gna_interval = true;

	if (delay->gna_interval.tv_sec >= 1)
		log_message(LOG_INFO, "The gna_interval is very large - %s seconds", FMT_STR_VSLOT(strvec,1));
}
