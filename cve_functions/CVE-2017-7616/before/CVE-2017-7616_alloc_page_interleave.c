static struct page *alloc_page_interleave(gfp_t gfp, unsigned order,
					unsigned nid)
{
	struct zonelist *zl;
	struct page *page;

	zl = node_zonelist(nid, gfp);
	page = __alloc_pages(gfp, order, zl);
	if (page && page_zone(page) == zonelist_zone(&zl->_zonerefs[0]))
		inc_zone_page_state(page, NUMA_INTERLEAVE_HIT);
	return page;
}
