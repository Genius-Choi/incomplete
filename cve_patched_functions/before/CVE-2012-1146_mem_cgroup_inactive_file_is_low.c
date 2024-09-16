int mem_cgroup_inactive_file_is_low(struct mem_cgroup *memcg, struct zone *zone)
{
	unsigned long active;
	unsigned long inactive;
	int zid = zone_idx(zone);
	int nid = zone_to_nid(zone);

	inactive = mem_cgroup_zone_nr_lru_pages(memcg, nid, zid,
						BIT(LRU_INACTIVE_FILE));
	active = mem_cgroup_zone_nr_lru_pages(memcg, nid, zid,
					      BIT(LRU_ACTIVE_FILE));

	return (active > inactive);
}
