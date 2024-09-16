free_global_data(data_t * data)
{
	if (!data)
		return;

	free_list(&data->email);
#if HAVE_DECL_CLONE_NEWNET
	FREE_PTR(data->network_namespace);
#endif
	FREE_PTR(data->instance_name);
	FREE_PTR(data->router_id);
	FREE_PTR(data->email_from);
	FREE_PTR(data->smtp_helo_name);
	FREE_PTR(data->local_name);
#ifdef _WITH_SNMP_
	FREE_PTR(data->snmp_socket);
#endif
#if defined _WITH_LVS_ && defined _WITH_VRRP_
	FREE_PTR(data->lvs_syncd.ifname);
	FREE_PTR(data->lvs_syncd.vrrp_name);
#endif
	FREE_PTR(data->notify_fifo.name);
	free_notify_script(&data->notify_fifo.script);
#ifdef _WITH_VRRP_
	FREE_PTR(data->default_ifname);
	FREE_PTR(data->vrrp_notify_fifo.name);
	free_notify_script(&data->vrrp_notify_fifo.script);
#endif
#ifdef _WITH_LVS_
	FREE_PTR(data->lvs_notify_fifo.name);
	free_notify_script(&data->lvs_notify_fifo.script);
#endif
	FREE(data);
}
