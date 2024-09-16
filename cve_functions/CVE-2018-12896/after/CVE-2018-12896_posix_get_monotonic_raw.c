static int posix_get_monotonic_raw(clockid_t which_clock, struct timespec64 *tp)
{
	ktime_get_raw_ts64(tp);
	return 0;
}
