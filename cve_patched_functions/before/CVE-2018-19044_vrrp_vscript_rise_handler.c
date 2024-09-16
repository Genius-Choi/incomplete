vrrp_vscript_rise_handler(vector_t *strvec)
{
	vrrp_script_t *vscript = LIST_TAIL_DATA(vrrp_data->vrrp_script);
	unsigned rise;

	if (!read_unsigned_strvec(strvec, 1, &rise, 1, INT_MAX, true)) {
		report_config_error(CONFIG_GENERAL_ERROR, "(%s): vrrp script rise value '%s' invalid, defaulting to 1", vscript->sname, FMT_STR_VSLOT(strvec, 1));
		vscript->rise = 1;
	}
	else
		vscript->rise = rise;
}
