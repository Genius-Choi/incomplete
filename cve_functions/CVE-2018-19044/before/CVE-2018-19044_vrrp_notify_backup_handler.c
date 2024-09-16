vrrp_notify_backup_handler(vector_t *strvec)
{
	vrrp_t *vrrp = LIST_TAIL_DATA(vrrp_data->vrrp);
	if (vrrp->script_backup) {
		report_config_error(CONFIG_GENERAL_ERROR, "(%s) notify_backup script already specified - ignoring %s", vrrp->iname, FMT_STR_VSLOT(strvec,1));
		return;
	}
	vrrp->script_backup = set_vrrp_notify_script(strvec, 0);
	vrrp->notify_exec = true;
}
