vrrp_iptables_handler(vector_t *strvec)
{
	global_data->vrrp_iptables_inchain[0] = '\0';
	global_data->vrrp_iptables_outchain[0] = '\0';
	if (vector_size(strvec) >= 2) {
		if (strlen(strvec_slot(strvec,1)) >= sizeof(global_data->vrrp_iptables_inchain)-1) {
			report_config_error(CONFIG_GENERAL_ERROR, "VRRP Error : iptables in chain name too long - ignored");
			return;
		}
		strcpy(global_data->vrrp_iptables_inchain, strvec_slot(strvec,1));
	}
	if (vector_size(strvec) >= 3) {
		if (strlen(strvec_slot(strvec,2)) >= sizeof(global_data->vrrp_iptables_outchain)-1) {
			report_config_error(CONFIG_GENERAL_ERROR, "VRRP Error : iptables out chain name too long - ignored");
			return;
		}
		strcpy(global_data->vrrp_iptables_outchain, strvec_slot(strvec,2));
	}
}
