vrrp_gnotify_fault_handler(vector_t *strvec)
{
	vrrp_sgroup_t *vgroup = LIST_TAIL_DATA(vrrp_data->vrrp_sync_group);
	if (vgroup->script_fault) {
		report_config_error(CONFIG_GENERAL_ERROR, "vrrp group %s: notify_fault script already specified - ignoring %s", vgroup->gname, FMT_STR_VSLOT(strvec,1));
		return;
	}
	vgroup->script_fault = set_vrrp_notify_script(strvec, 0);
	vgroup->notify_exec = true;
}
