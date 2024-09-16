struct lruvec *mem_cgroup_zone_lruvec(struct zone *zone,
				      struct mem_cgroup *memcg)
{
	struct mem_cgroup_per_zone *mz;

	if (mem_cgroup_disabled())
		return &zone->lruvec;

	mz = mem_cgroup_zoneinfo(memcg, zone_to_nid(zone), zone_idx(zone));
	return &mz->lruvec;
}
