get_netlink_rcv_bufs_size(vector_t *strvec, const char *type)
{
	unsigned val;

	if (!strvec)
		return 0;

	if (vector_size(strvec) < 2) {
		report_config_error(CONFIG_GENERAL_ERROR, "%s_rcv_bufs size missing", type);
		return 0;
	}

	if (!read_unsigned_strvec(strvec, 1, &val, 0, UINT_MAX, false)) {
		report_config_error(CONFIG_GENERAL_ERROR, "%s_rcv_bufs size (%s) invalid", type, FMT_STR_VSLOT(strvec, 1));
		return 0;
	}

	return val;
}
