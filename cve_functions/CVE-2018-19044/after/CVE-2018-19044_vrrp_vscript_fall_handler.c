vrrp_vscript_fall_handler(vector_t *strvec)
{
	vrrp_script_t *vscript = LIST_TAIL_DATA(vrrp_data->vrrp_script);
	unsigned fall;

	if (!read_unsigned_strvec(strvec, 1, &fall, 1, INT_MAX, true)) {
		report_config_error(CONFIG_GENERAL_ERROR, "(%s): vrrp script fall value '%s' invalid, defaulting to 1", vscript->sname, FMT_STR_VSLOT(strvec, 1));
		vscript->fall = 1;
	}
	else
		vscript->fall = fall;
}
