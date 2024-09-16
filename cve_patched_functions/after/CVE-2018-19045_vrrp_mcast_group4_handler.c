vrrp_mcast_group4_handler(vector_t *strvec)
{
	struct sockaddr_in *mcast = &global_data->vrrp_mcast_group4;
	int ret;

	ret = inet_stosockaddr(strvec_slot(strvec, 1), 0, (struct sockaddr_storage *)mcast);
	if (ret < 0) {
		report_config_error(CONFIG_GENERAL_ERROR, "Configuration error: Cant parse vrrp_mcast_group4 [%s]. Skipping"
				   , FMT_STR_VSLOT(strvec, 1));
	}
}
