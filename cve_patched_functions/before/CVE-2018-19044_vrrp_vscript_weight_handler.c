vrrp_vscript_weight_handler(vector_t *strvec)
{
	vrrp_script_t *vscript = LIST_TAIL_DATA(vrrp_data->vrrp_script);
	int weight;

	if (!read_int_strvec(strvec, 1, &weight, -253, 253, true))
		report_config_error(CONFIG_GENERAL_ERROR, "vrrp_script %s weight %s must be in [-253, 253]", vscript->sname, FMT_STR_VSLOT(strvec, 1));
	vscript->weight = weight;
}
