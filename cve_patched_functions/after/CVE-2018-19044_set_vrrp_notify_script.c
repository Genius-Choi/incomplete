set_vrrp_notify_script(__attribute__((unused)) vector_t *strvec, int extra_params)
{
	return notify_script_init(extra_params, "notify");
}
