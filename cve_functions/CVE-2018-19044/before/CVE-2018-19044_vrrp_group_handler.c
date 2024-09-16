vrrp_group_handler(vector_t *strvec)
{
	vrrp_sgroup_t *vgroup = LIST_TAIL_DATA(vrrp_data->vrrp_sync_group);

	if (vgroup->iname) {
		report_config_error(CONFIG_GENERAL_ERROR, "Group list already specified for sync group %s", vgroup->gname);
		skip_block(true);
		return;
	}

	vgroup->iname = read_value_block(strvec);

	if (!vgroup->iname)
		report_config_error(CONFIG_GENERAL_ERROR, "Warning - sync group %s has empty group block", vgroup->gname);
}
