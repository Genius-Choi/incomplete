static_routes_handler(vector_t *strvec)
{
	global_data->have_vrrp_config = true;

	if (!strvec)
		return;

	alloc_value_block(alloc_sroute, vector_slot(strvec, 0));
}
