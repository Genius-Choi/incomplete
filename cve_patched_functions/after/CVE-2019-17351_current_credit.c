static long current_credit(void)
{
	return balloon_stats.target_pages - balloon_stats.current_pages;
}
