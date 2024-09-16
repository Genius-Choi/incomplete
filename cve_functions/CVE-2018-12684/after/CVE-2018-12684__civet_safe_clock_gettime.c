_civet_safe_clock_gettime(int clk_id, struct timespec *t)
{
	if (clock_gettime) {
		return clock_gettime(clk_id, t);
	}
	return _civet_clock_gettime(clk_id, t);
}
