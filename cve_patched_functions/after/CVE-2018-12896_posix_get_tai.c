static int posix_get_tai(clockid_t which_clock, struct timespec64 *tp)
{
	ktime_get_clocktai_ts64(tp);
	return 0;
}
