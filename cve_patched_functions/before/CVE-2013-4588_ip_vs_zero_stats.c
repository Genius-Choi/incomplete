ip_vs_zero_stats(struct ip_vs_stats *stats)
{
	spin_lock_bh(&stats->lock);

	memset(&stats->ustats, 0, sizeof(stats->ustats));
	ip_vs_zero_estimator(stats);

	spin_unlock_bh(&stats->lock);
}
