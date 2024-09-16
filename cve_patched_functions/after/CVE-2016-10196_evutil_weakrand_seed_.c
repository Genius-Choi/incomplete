evutil_weakrand_seed_(struct evutil_weakrand_state *state, ev_uint32_t seed)
{
	if (seed == 0) {
		struct timeval tv;
		evutil_gettimeofday(&tv, NULL);
		seed = (ev_uint32_t)tv.tv_sec + (ev_uint32_t)tv.tv_usec;
#ifdef _WIN32
		seed += (ev_uint32_t) _getpid();
#else
		seed += (ev_uint32_t) getpid();
#endif
	}
	state->seed = seed;
	return seed;
}
