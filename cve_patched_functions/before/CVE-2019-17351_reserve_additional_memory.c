static enum bp_state reserve_additional_memory(void)
{
	balloon_stats.target_pages = balloon_stats.current_pages;
	return BP_ECANCELED;
}
