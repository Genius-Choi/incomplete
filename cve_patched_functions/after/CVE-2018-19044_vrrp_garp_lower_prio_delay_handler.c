vrrp_garp_lower_prio_delay_handler(vector_t *strvec)
{
	vrrp_t *vrrp = LIST_TAIL_DATA(vrrp_data->vrrp);
	unsigned delay;

	if (!read_unsigned_strvec(strvec, 1, &delay, 0, UINT_MAX / TIMER_HZ, true)) {
		report_config_error(CONFIG_GENERAL_ERROR, "(%s): garp_lower_prio_delay '%s' invalid - ignoring", vrrp->iname, FMT_STR_VSLOT(strvec, 1));
		return;
	}

	vrrp->garp_lower_prio_delay = delay * TIMER_HZ;
}
