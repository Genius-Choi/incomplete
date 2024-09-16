vrrp_unicast_peer_handler(vector_t *strvec)
{
	alloc_value_block(alloc_vrrp_unicast_peer, vector_slot(strvec, 0));
}
