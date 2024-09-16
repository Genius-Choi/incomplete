int g_timeval_cmp(const GTimeVal *tv1, const GTimeVal *tv2)
{
	if (tv1->tv_sec < tv2->tv_sec)
		return -1;
	if (tv1->tv_sec > tv2->tv_sec)
		return 1;

	return tv1->tv_usec < tv2->tv_usec ? -1 :
		tv1->tv_usec > tv2->tv_usec ? 1 : 0;
}
