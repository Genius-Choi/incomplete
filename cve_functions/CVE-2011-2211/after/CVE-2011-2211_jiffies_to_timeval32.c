jiffies_to_timeval32(unsigned long jiffies, struct timeval32 *value)
{
	value->tv_usec = (jiffies % HZ) * (1000000L / HZ);
	value->tv_sec = jiffies / HZ;
}
