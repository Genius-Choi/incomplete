void llc_sysctl_exit(void)
{
	if (llc2_timeout_header) {
		unregister_net_sysctl_table(llc2_timeout_header);
		llc2_timeout_header = NULL;
	}
	if (llc_station_header) {
		unregister_net_sysctl_table(llc_station_header);
		llc_station_header = NULL;
	}
}
