vrrp_smtp_handler(__attribute__((unused)) vector_t *strvec)
{
	vrrp_t *vrrp = LIST_TAIL_DATA(vrrp_data->vrrp);
	int res = true;

	if (vector_size(strvec) >= 2) {
		res = check_true_false(strvec_slot(strvec, 1));
		if (res == -1) {
			report_config_error(CONFIG_GENERAL_ERROR, "Invalid vrrp_instance smtp_alert parameter %s", FMT_STR_VSLOT(strvec, 1));
			return;
		}
	}
	vrrp->smtp_alert = res;
}
