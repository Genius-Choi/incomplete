vrrp_debug_handler(vector_t *strvec)
{
	vrrp_t *vrrp = LIST_TAIL_DATA(vrrp_data->vrrp);
	unsigned debug;

	if (!read_unsigned_strvec(strvec, 1, &debug, 0, 4, true))
		report_config_error(CONFIG_GENERAL_ERROR, "(%s) Debug value '%s' not valid; must be between 0-4", vrrp->iname, FMT_STR_VSLOT(strvec, 1));
	else
		vrrp->debug = debug;
}
