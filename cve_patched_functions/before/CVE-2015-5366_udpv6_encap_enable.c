void udpv6_encap_enable(void)
{
	if (!static_key_enabled(&udpv6_encap_needed))
		static_key_slow_inc(&udpv6_encap_needed);
}
