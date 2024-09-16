struct lruvec *mem_cgroup_lru_add_list(struct zone *zone, struct page *page,
				       enum lru_list lru)
{
	struct mem_cgroup_per_zone *mz;
	struct mem_cgroup *memcg;
	struct page_cgroup *pc;

	if (mem_cgroup_disabled())
		return &zone->lruvec;

	pc = lookup_page_cgroup(page);
	memcg = pc->mem_cgroup;
	mz = page_cgroup_zoneinfo(memcg, page);
	/* compound_order() is stabilized through lru_lock */
	MEM_CGROUP_ZSTAT(mz, lru) += 1 << compound_order(page);
	return &mz->lruvec;
}
