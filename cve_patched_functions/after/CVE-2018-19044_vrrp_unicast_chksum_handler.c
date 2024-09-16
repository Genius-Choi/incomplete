vrrp_unicast_chksum_handler(vector_t *strvec)
{
	vrrp_t *vrrp = LIST_TAIL_DATA(vrrp_data->vrrp);

	if (vector_size(strvec) >= 2) {
		if (!strcmp(strvec_slot(strvec, 1), "never"))
			vrrp->unicast_chksum_compat = CHKSUM_COMPATIBILITY_NEVER;
		else
			report_config_error(CONFIG_GENERAL_ERROR, "(%s) Unknown old_unicast_chksum mode %s - ignoring", vrrp->iname, FMT_STR_VSLOT(strvec, 1));
	}
	else
		vrrp->unicast_chksum_compat = CHKSUM_COMPATIBILITY_CONFIG;
}
