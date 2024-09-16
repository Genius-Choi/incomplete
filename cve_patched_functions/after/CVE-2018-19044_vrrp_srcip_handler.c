vrrp_srcip_handler(vector_t *strvec)
{
	vrrp_t *vrrp = LIST_TAIL_DATA(vrrp_data->vrrp);
	struct sockaddr_storage *saddr = &vrrp->saddr;

	if (inet_stosockaddr(strvec_slot(strvec, 1), NULL, saddr)) {
		report_config_error(CONFIG_GENERAL_ERROR, "Configuration error: VRRP instance[%s] malformed"
				     " src address[%s]. Skipping..."
				   , vrrp->iname, FMT_STR_VSLOT(strvec, 1));
		return;
	}

	vrrp->saddr_from_config = true;

	if (vrrp->family == AF_UNSPEC)
		vrrp->family = saddr->ss_family;
	else if (saddr->ss_family != vrrp->family) {
		report_config_error(CONFIG_GENERAL_ERROR, "Configuration error: VRRP instance[%s] and src address"
				     "[%s] MUST be of the same family !!! Skipping..."
				   , vrrp->iname, FMT_STR_VSLOT(strvec, 1));
		saddr->ss_family = AF_UNSPEC;
		vrrp->saddr_from_config = false;
	}
}
