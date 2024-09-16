void net_inc_ingress_queue(void)
{
	static_key_slow_inc(&ingress_needed);
}
