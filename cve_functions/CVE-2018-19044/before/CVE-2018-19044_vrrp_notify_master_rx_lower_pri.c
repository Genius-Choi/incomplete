vrrp_notify_master_rx_lower_pri(vector_t *strvec)
{
	vrrp_t *vrrp = LIST_TAIL_DATA(vrrp_data->vrrp);
	if (vrrp->script_master_rx_lower_pri) {
		report_config_error(CONFIG_GENERAL_ERROR, "(%s) notify_master_rx_lower_pri script already specified - ignoring %s", vrrp->iname, FMT_STR_VSLOT(strvec,1));
		return;
	}
	vrrp->script_master_rx_lower_pri = set_vrrp_notify_script(strvec, 0);
	vrrp->notify_exec = true;
}
