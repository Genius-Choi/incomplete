static struct page *balloon_retrieve(bool require_lowmem)
{
	struct page *page;

	if (list_empty(&ballooned_pages))
		return NULL;

	page = list_entry(ballooned_pages.next, struct page, lru);
	if (require_lowmem && PageHighMem(page))
		return NULL;
	list_del(&page->lru);

	if (PageHighMem(page))
		balloon_stats.balloon_high--;
	else
		balloon_stats.balloon_low--;

	return page;
}
