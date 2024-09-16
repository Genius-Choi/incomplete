vrrp_garp_refresh_handler(vector_t *strvec)
{
	vrrp_t *vrrp = LIST_TAIL_DATA(vrrp_data->vrrp);
	unsigned refresh;

	if (!read_unsigned_strvec(strvec, 1, &refresh, 0, UINT_MAX, true)) {
		report_config_error(CONFIG_GENERAL_ERROR, "(%s): Invalid garp_master_refresh '%s' - ignoring", vrrp->iname, FMT_STR_VSLOT(strvec, 1));
		vrrp->garp_refresh.tv_sec = 0;
	}
	else
		vrrp->garp_refresh.tv_sec = refresh;
	vrrp->garp_refresh.tv_usec = 0;
}
