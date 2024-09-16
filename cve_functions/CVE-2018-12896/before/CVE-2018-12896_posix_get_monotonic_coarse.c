static int posix_get_monotonic_coarse(clockid_t which_clock,
						struct timespec64 *tp)
{
	ktime_get_coarse_ts64(tp);
	return 0;
}
