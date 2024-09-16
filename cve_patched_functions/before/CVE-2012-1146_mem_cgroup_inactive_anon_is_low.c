int mem_cgroup_inactive_anon_is_low(struct mem_cgroup *memcg, struct zone *zone)
{
	unsigned long inactive_ratio;
	int nid = zone_to_nid(zone);
	int zid = zone_idx(zone);
	unsigned long inactive;
	unsigned long active;
	unsigned long gb;

	inactive = mem_cgroup_zone_nr_lru_pages(memcg, nid, zid,
						BIT(LRU_INACTIVE_ANON));
	active = mem_cgroup_zone_nr_lru_pages(memcg, nid, zid,
					      BIT(LRU_ACTIVE_ANON));

	gb = (inactive + active) >> (30 - PAGE_SHIFT);
	if (gb)
		inactive_ratio = int_sqrt(10 * gb);
	else
		inactive_ratio = 1;

	return inactive * inactive_ratio < active;
}
