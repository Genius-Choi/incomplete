vrrp_vscript_end_handler(void)
{
	vrrp_script_t *vscript = LIST_TAIL_DATA(vrrp_data->vrrp_script);

	if (!vscript->script.args || !vscript->script.args[0]) {
		report_config_error(CONFIG_GENERAL_ERROR, "No script set for vrrp_script %s - removing", vscript->sname);
		remove_script = true;
	}
	else if (!remove_script) {
		if (script_user_set)
			return;

		if (set_default_script_user(NULL, NULL)) {
			report_config_error(CONFIG_GENERAL_ERROR, "Unable to set default user for vrrp script %s - removing", vscript->sname);
			remove_script = true;
		}
	}

	if (remove_script) {
		free_list_element(vrrp_data->vrrp_script, vrrp_data->vrrp_script->tail);
		return;
	}

	vscript->script.uid = default_script_uid;
	vscript->script.gid = default_script_gid;
}
