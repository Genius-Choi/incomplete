vrrp_auth_type_handler(vector_t *strvec)
{
	vrrp_t *vrrp = LIST_TAIL_DATA(vrrp_data->vrrp);
	char *str = strvec_slot(strvec, 1);

	if (!strcmp(str, "AH"))
		vrrp->auth_type = VRRP_AUTH_AH;
	else if (!strcmp(str, "PASS"))
		vrrp->auth_type = VRRP_AUTH_PASS;
	else
		report_config_error(CONFIG_GENERAL_ERROR, "(%s) unknown authentication type '%s'", vrrp->iname, str);
}
