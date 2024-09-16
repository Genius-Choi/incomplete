encode_time3(__be32 *p, struct timespec *time)
{
	*p++ = htonl((u32) time->tv_sec); *p++ = htonl(time->tv_nsec);
	return p;
}
