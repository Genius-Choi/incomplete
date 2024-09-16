vrrp_check_adv_addr_handler(__attribute__((unused)) vector_t *strvec)
{
	global_data->vrrp_skip_check_adv_addr = 1;
}
