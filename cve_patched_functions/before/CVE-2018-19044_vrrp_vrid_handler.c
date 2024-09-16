vrrp_vrid_handler(vector_t *strvec)
{
	vrrp_t *vrrp = LIST_TAIL_DATA(vrrp_data->vrrp);
	unsigned vrid;

	if (!read_unsigned_strvec(strvec, 1, &vrid, 1, 255, false)) {
		report_config_error(CONFIG_GENERAL_ERROR, "(%s): VRID '%s' not valid - must be between 1 & 255", vrrp->iname, FMT_STR_VSLOT(strvec, 1));
		return;
	}

	vrrp->vrid = (uint8_t)vrid;
}
