vrrp_int_handler(vector_t *strvec)
{
	vrrp_t *vrrp = LIST_TAIL_DATA(vrrp_data->vrrp);
	char *name = strvec_slot(strvec, 1);

	if (strlen(name) >= IFNAMSIZ) {
		report_config_error(CONFIG_GENERAL_ERROR, "Interface name '%s' too long - ignoring", name);
		return;
	}

	vrrp->ifp = if_get_by_ifname(name, IF_CREATE_IF_DYNAMIC);
	if (!vrrp->ifp)
		report_config_error(CONFIG_GENERAL_ERROR, "WARNING - interface %s for vrrp_instance %s doesn't exist", name, vrrp->iname);
	else if (vrrp->ifp->hw_type == ARPHRD_LOOPBACK) {
		report_config_error(CONFIG_GENERAL_ERROR, "(%s) cannot use a loopback interface (%s) for vrrp - ignoring", vrrp->iname, vrrp->ifp->ifname);
		vrrp->ifp = NULL;
	}

#ifdef _HAVE_VRRP_VMAC_
	vrrp->configured_ifp = vrrp->ifp;
#endif
}
