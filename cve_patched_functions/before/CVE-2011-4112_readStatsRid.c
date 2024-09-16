static int readStatsRid(struct airo_info*ai, StatsRid *sr, int rid, int lock)
{
	return PC4500_readrid(ai, rid, sr, sizeof(*sr), lock);
}
