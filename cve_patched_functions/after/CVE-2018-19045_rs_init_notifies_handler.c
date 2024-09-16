rs_init_notifies_handler(vector_t *strvec)
{
	int res = true;

	if (vector_size(strvec) >= 2) {
		res = check_true_false(strvec_slot(strvec,1));
		if (res < 0) {
			report_config_error(CONFIG_GENERAL_ERROR, "Invalid value '%s' for global rs_init_notifies specified", FMT_STR_VSLOT(strvec, 1));
			return;
		}
	}

	global_data->rs_init_notifies = res;
}
