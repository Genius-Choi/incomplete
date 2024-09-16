static bool balloon_is_inflated(void)
{
	return balloon_stats.balloon_low || balloon_stats.balloon_high;
}
