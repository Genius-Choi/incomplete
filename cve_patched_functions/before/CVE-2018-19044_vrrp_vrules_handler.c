vrrp_vrules_handler(vector_t *strvec)
{
	alloc_value_block(alloc_vrrp_vrule, vector_slot(strvec, 0));
}
