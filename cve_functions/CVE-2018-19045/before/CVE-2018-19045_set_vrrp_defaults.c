set_vrrp_defaults(data_t * data)
{
	data->vrrp_garp_rep = VRRP_GARP_REP;
	data->vrrp_garp_refresh.tv_sec = VRRP_GARP_REFRESH;
	data->vrrp_garp_refresh_rep = VRRP_GARP_REFRESH_REP;
	data->vrrp_garp_delay = VRRP_GARP_DELAY;
	data->vrrp_garp_lower_prio_delay = PARAMETER_UNSET;
	data->vrrp_garp_lower_prio_rep = PARAMETER_UNSET;
	data->vrrp_lower_prio_no_advert = false;
	data->vrrp_higher_prio_send_advert = false;
	data->vrrp_version = VRRP_VERSION_2;
	strcpy(data->vrrp_iptables_inchain, "INPUT");
#ifdef _HAVE_LIBIPSET_
	data->using_ipsets = true;
	strcpy(data->vrrp_ipset_address, "keepalived");
	strcpy(data->vrrp_ipset_address6, "keepalived6");
	strcpy(data->vrrp_ipset_address_iface6, "keepalived_if6");
#endif
	data->vrrp_check_unicast_src = false;
	data->vrrp_skip_check_adv_addr = false;
	data->vrrp_strict = false;
}
