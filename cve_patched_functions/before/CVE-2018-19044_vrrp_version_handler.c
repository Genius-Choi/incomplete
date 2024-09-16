vrrp_version_handler(vector_t *strvec)
{
	vrrp_t *vrrp = LIST_TAIL_DATA(vrrp_data->vrrp);
	int version;

	if (!read_int_strvec(strvec, 1, &version, 2, 3, true)) {
		report_config_error(CONFIG_GENERAL_ERROR, "(%s): Version must be either 2 or 3", vrrp->iname);
		return;
	}

	if ((vrrp->version && vrrp->version != version) ||
	    (version == VRRP_VERSION_2 && vrrp->family == AF_INET6)) {
		report_config_error(CONFIG_GENERAL_ERROR, "(%s) vrrp_version %d conflicts with configured or deduced version %d; ignoring.", vrrp->iname, version, vrrp->version);
		return;
	}

	vrrp->version = version;
}
