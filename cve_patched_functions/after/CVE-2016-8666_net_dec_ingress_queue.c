void net_dec_ingress_queue(void)
{
	static_key_slow_dec(&ingress_needed);
}
