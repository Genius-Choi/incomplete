vrrp_notify_handler(vector_t *strvec)
{
	vrrp_t *vrrp = LIST_TAIL_DATA(vrrp_data->vrrp);
	if (vrrp->script) {
		report_config_error(CONFIG_GENERAL_ERROR, "(%s) notify script already specified - ignoring %s", vrrp->iname, FMT_STR_VSLOT(strvec,1));
		return;
	}
	vrrp->script = set_vrrp_notify_script(strvec, 4);
	vrrp->notify_exec = true;
}
