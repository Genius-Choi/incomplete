void net_enable_timestamp(void)
{
#ifdef HAVE_JUMP_LABEL
	int deferred = atomic_xchg(&netstamp_needed_deferred, 0);

	if (deferred) {
		while (--deferred)
			static_key_slow_dec(&netstamp_needed);
		return;
	}
#endif
	static_key_slow_inc(&netstamp_needed);
}
