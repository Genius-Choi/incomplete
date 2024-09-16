void net_dec_egress_queue(void)
{
	static_key_slow_dec(&egress_needed);
}
