static void gather_stats(struct page *page, struct numa_maps *md, int pte_dirty,
			unsigned long nr_pages)
{
	int count = page_mapcount(page);

	md->pages += nr_pages;
	if (pte_dirty || PageDirty(page))
		md->dirty += nr_pages;

	if (PageSwapCache(page))
		md->swapcache += nr_pages;

	if (PageActive(page) || PageUnevictable(page))
		md->active += nr_pages;

	if (PageWriteback(page))
		md->writeback += nr_pages;

	if (PageAnon(page))
		md->anon += nr_pages;

	if (count > md->mapcount_max)
		md->mapcount_max = count;

	md->node[page_to_nid(page)] += nr_pages;
}
