mem_cgroup_zone_nr_lru_pages(struct mem_cgroup *memcg, int nid, int zid,
			unsigned int lru_mask)
{
	struct mem_cgroup_per_zone *mz;
	enum lru_list l;
	unsigned long ret = 0;

	mz = mem_cgroup_zoneinfo(memcg, nid, zid);

	for_each_lru(l) {
		if (BIT(l) & lru_mask)
			ret += MEM_CGROUP_ZSTAT(mz, l);
	}
	return ret;
}
