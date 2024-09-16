static u64 cvt_kvaddr(void *p)
{
	struct page *page;
	u64 paddr = 0;

	page = vmalloc_to_page(p);
	if (page)
		paddr = page_to_pfn(page) << PAGE_SHIFT;

	return paddr;
}
