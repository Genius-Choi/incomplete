void net_inc_egress_queue(void)
{
	static_key_slow_inc(&egress_needed);
}
