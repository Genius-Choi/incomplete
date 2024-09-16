vrrp_notify_master_handler(vector_t *strvec)
{
	vrrp_t *vrrp = LIST_TAIL_DATA(vrrp_data->vrrp);
	if (vrrp->script_master) {
		report_config_error(CONFIG_GENERAL_ERROR, "(%s) notify_master script already specified - ignoring %s", vrrp->iname, FMT_STR_VSLOT(strvec,1));
		return;
	}
	vrrp->script_master = set_vrrp_notify_script(strvec, 0);
	vrrp->notify_exec = true;
}
