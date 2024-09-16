vrrp_vip_handler(vector_t *strvec)
{
	alloc_value_block(alloc_vrrp_vip, vector_slot(strvec, 0));
}
