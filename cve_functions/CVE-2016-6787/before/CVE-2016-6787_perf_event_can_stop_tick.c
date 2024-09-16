bool perf_event_can_stop_tick(void)
{
	if (atomic_read(&nr_freq_events) ||
	    __this_cpu_read(perf_throttled_count))
		return false;
	else
		return true;
}
