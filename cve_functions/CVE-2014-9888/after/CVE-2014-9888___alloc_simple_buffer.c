static void *__alloc_simple_buffer(struct device *dev, size_t size, gfp_t gfp,
				   struct page **ret_page)
{
	struct page *page;
	page = __dma_alloc_buffer(dev, size, gfp);
	if (!page)
		return NULL;

	*ret_page = page;
	return page_address(page);
}
