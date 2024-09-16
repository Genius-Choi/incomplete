page_cgroup_zoneinfo(struct mem_cgroup *memcg, struct page *page)
{
	int nid = page_to_nid(page);
	int zid = page_zonenum(page);

	return mem_cgroup_zoneinfo(memcg, nid, zid);
}
