decode_time3(__be32 *p, struct timespec *time)
{
	time->tv_sec = ntohl(*p++);
	time->tv_nsec = ntohl(*p++);
	return p;
}
