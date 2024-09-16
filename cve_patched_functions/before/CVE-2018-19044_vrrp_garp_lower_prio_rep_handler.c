vrrp_garp_lower_prio_rep_handler(vector_t *strvec)
{
	vrrp_t *vrrp = LIST_TAIL_DATA(vrrp_data->vrrp);
	unsigned garp_lower_prio_rep;

	if (!read_unsigned_strvec(strvec, 1, &garp_lower_prio_rep, 0, INT_MAX, true)) {
		report_config_error(CONFIG_GENERAL_ERROR, "(%s): Invalid garp_lower_prio_repeat '%s'", vrrp->iname, FMT_STR_VSLOT(strvec, 1));
		return;
	}

	vrrp->garp_lower_prio_rep = garp_lower_prio_rep;
}
