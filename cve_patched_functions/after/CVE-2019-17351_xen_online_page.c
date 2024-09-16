static void xen_online_page(struct page *page, unsigned int order)
{
	unsigned long i, size = (1 << order);
	unsigned long start_pfn = page_to_pfn(page);
	struct page *p;

	pr_debug("Online %lu pages starting at pfn 0x%lx\n", size, start_pfn);
	mutex_lock(&balloon_mutex);
	for (i = 0; i < size; i++) {
		p = pfn_to_page(start_pfn + i);
		__online_page_set_limits(p);
		__SetPageOffline(p);
		__balloon_append(p);
	}
	mutex_unlock(&balloon_mutex);
}
