vrrp_rx_bufs_multiplier_handler(vector_t *strvec)
{
	unsigned rx_buf_mult;

	if (!strvec)
		return;

	if (vector_size(strvec) != 2) {
		report_config_error(CONFIG_GENERAL_ERROR, "Invalid vrrp_rx_bufs_multiplier");
		return;
	}

	if (!read_unsigned_strvec(strvec, 1, &rx_buf_mult, 1, UINT_MAX, false))
		report_config_error(CONFIG_GENERAL_ERROR, "Invalid vrrp_rx_bufs_multiplier %s", FMT_STR_VSLOT(strvec, 1));
	else
		global_data->vrrp_rx_bufs_multiples = rx_buf_mult;
}
