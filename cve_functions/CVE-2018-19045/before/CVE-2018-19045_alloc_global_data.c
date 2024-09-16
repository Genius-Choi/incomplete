alloc_global_data(void)
{
	data_t *new;

	if (global_data)
		return global_data;

	new = (data_t *) MALLOC(sizeof(data_t));
	new->email = alloc_list(free_email, dump_email);
	new->smtp_alert = -1;
#ifdef _WITH_VRRP_
	new->smtp_alert_vrrp = -1;
#endif
#ifdef _WITH_LVS_
	new->smtp_alert_checker = -1;
#endif

#ifdef _WITH_VRRP_
	set_default_mcast_group(new);
	set_vrrp_defaults(new);
#endif
	new->notify_fifo.fd = -1;
#ifdef _WITH_VRRP_
	new->vrrp_notify_fifo.fd = -1;
#if HAVE_DECL_RLIMIT_RTTIME == 1
	new->vrrp_rlimit_rt = RT_RLIMIT_DEFAULT;
#endif
	new->vrrp_rx_bufs_multiples = 3;
#endif
#ifdef _WITH_LVS_
	new->lvs_notify_fifo.fd = -1;
#if HAVE_DECL_RLIMIT_RTTIME == 1
	new->checker_rlimit_rt = RT_RLIMIT_DEFAULT;
#endif
#ifdef _WITH_BFD_
#if HAVE_DECL_RLIMIT_RTTIME == 1
	new->bfd_rlimit_rt = RT_RLIMIT_DEFAULT;
#endif
#endif
#endif

#ifdef _WITH_SNMP_
	if (snmp) {
#ifdef _WITH_SNMP_VRRP_
		new->enable_snmp_vrrp = true;
#endif
#ifdef _WITH_SNMP_RFCV2_
		new->enable_snmp_rfcv2 = true;
#endif
#ifdef _WITH_SNMP_RFCV3_
		new->enable_snmp_rfcv3 = true;
#endif
#ifdef _WITH_SNMP_CHECKER_
		new->enable_snmp_checker = true;
#endif
	}

	if (snmp_socket) {
		new->snmp_socket = MALLOC(strlen(snmp_socket + 1));
		strcpy(new->snmp_socket, snmp_socket);
	}
#endif

#ifdef _WITH_LVS_
#ifdef _WITH_VRRP_
	new->lvs_syncd.syncid = PARAMETER_UNSET;
#ifdef _HAVE_IPVS_SYNCD_ATTRIBUTES_
	new->lvs_syncd.mcast_group.ss_family = AF_UNSPEC;
#endif
#endif
#endif

	return new;
}
