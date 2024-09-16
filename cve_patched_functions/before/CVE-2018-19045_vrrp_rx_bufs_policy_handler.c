vrrp_rx_bufs_policy_handler(vector_t *strvec)
{
	unsigned rx_buf_size;
	unsigned i;

	if (!strvec)
		return;

	if (vector_size(strvec) < 2) {
		report_config_error(CONFIG_GENERAL_ERROR, "vrrp_rx_bufs_policy missing");
		return;
	}

	for (i = 1; i < vector_size(strvec); i++) {
		if (!strcasecmp(strvec_slot(strvec, i), "MTU"))
			global_data->vrrp_rx_bufs_policy |= RX_BUFS_POLICY_MTU;
		else if (!strcasecmp(strvec_slot(strvec, i), "ADVERT"))
			global_data->vrrp_rx_bufs_policy |= RX_BUFS_POLICY_ADVERT;
		else {
			if (!read_unsigned_strvec(strvec, 1, &rx_buf_size, 0, UINT_MAX, false))
				report_config_error(CONFIG_GENERAL_ERROR, "Invalid vrrp_rx_bufs_policy %s", FMT_STR_VSLOT(strvec, i));
			else {
				global_data->vrrp_rx_bufs_size = rx_buf_size;
				global_data->vrrp_rx_bufs_policy |= RX_BUFS_SIZE;
			}
		}
	}

	if ((global_data->vrrp_rx_bufs_policy & RX_BUFS_SIZE) &&
	    (global_data->vrrp_rx_bufs_policy & (RX_BUFS_POLICY_MTU | RX_BUFS_POLICY_ADVERT))) {
		report_config_error(CONFIG_GENERAL_ERROR, "Cannot set vrrp_rx_bufs_policy size and policy, ignoring policy");
		global_data->vrrp_rx_bufs_policy &= ~(RX_BUFS_POLICY_MTU | RX_BUFS_POLICY_ADVERT);
	}
	else if ((global_data->vrrp_rx_bufs_policy & RX_BUFS_POLICY_MTU) &&
		 (global_data->vrrp_rx_bufs_policy & RX_BUFS_POLICY_ADVERT)) {
		report_config_error(CONFIG_GENERAL_ERROR, "Cannot set both vrrp_rx_bufs_policy MTU and ADVERT, ignoring ADVERT");
		global_data->vrrp_rx_bufs_policy &= ~RX_BUFS_POLICY_ADVERT;
	}
}
