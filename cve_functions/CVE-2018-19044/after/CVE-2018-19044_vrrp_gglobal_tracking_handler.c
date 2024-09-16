vrrp_gglobal_tracking_handler(__attribute__((unused)) vector_t *strvec)
{
	vrrp_sgroup_t *vgroup = LIST_TAIL_DATA(vrrp_data->vrrp_sync_group);

	report_config_error(CONFIG_GENERAL_ERROR, "(%s) global_tracking is deprecated. Use track_interface/script/file on the sync group", vgroup->gname);
	vgroup->sgroup_tracking_weight = true;
}
