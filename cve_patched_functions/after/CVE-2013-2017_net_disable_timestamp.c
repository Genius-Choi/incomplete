void net_disable_timestamp(void)
{
	atomic_dec(&netstamp_needed);
}
