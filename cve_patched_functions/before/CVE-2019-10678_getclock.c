int getclock(struct timeval *tv) {
#ifdef CLOCK_MONOTONIC
	struct timespec ts;
		if (!clock_gettime(CLOCK_MONOTONIC, &ts)) {
			tv->tv_sec = ts.tv_sec;
			tv->tv_usec = ts.tv_nsec / 1000;
			return 0;
		}
#endif
	return gettimeofday(tv, NULL);
}
