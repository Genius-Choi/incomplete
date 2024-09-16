vrrp_prio_handler(vector_t *strvec)
{
	vrrp_t *vrrp = LIST_TAIL_DATA(vrrp_data->vrrp);
	unsigned base_priority;

	if (!read_unsigned_strvec(strvec, 1, &base_priority, 1, VRRP_PRIO_OWNER, false)) {
		report_config_error(CONFIG_GENERAL_ERROR, "(%s) Priority not valid! must be between 1 & %d. Using default %d", vrrp->iname, VRRP_PRIO_OWNER, VRRP_PRIO_DFL);
		vrrp->base_priority = VRRP_PRIO_DFL;
	}
	else
		vrrp->base_priority = (uint8_t)base_priority;
}
