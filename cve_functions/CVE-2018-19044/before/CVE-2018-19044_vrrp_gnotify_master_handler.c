vrrp_gnotify_master_handler(vector_t *strvec)
{
	vrrp_sgroup_t *vgroup = LIST_TAIL_DATA(vrrp_data->vrrp_sync_group);
	if (vgroup->script_master) {
		report_config_error(CONFIG_GENERAL_ERROR, "vrrp group %s: notify_master script already specified - ignoring %s", vgroup->gname, FMT_STR_VSLOT(strvec,1));
		return;
	}
	vgroup->script_master = set_vrrp_notify_script(strvec, 0);
	vgroup->notify_exec = true;
}
